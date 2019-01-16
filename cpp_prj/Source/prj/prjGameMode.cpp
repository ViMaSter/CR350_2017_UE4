// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "prjGameMode.h"

#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

#include "prjGameStateBase.h"
#include "prjPlayerState.h"
#include "prjHUD.h"

#include "LocalPlayerController.h"
#include "RemotePlayerController.h"

#include "WebSocketBlueprintLibrary.h"

#include "DataFormats/Command.h"
#include "DataFormats/PlayerData.h"
#include "DataFormats/Request/CreateSession.h"
#include "DataFormats/Response/SessionJoin.h"
#include "DataFormats/Response/SessionUpdate.h"
#include "DataFormats/Response/SessionLeave.h"
#include "DataFormats/Response/PlayerJoin.h"
#include "DataFormats/Response/PlayerUpdate.h"
#include "DataFormats/Request/CreateSession.h"

void AprjGameMode::StartPlay()
{
	Super::StartPlay();

	FScriptDelegate OnMessageDelegate;
	OnMessageDelegate.BindUFunction(this, "OnCommandReceived");
	this->OnWebsocketCommand.Add(OnMessageDelegate);
	UE_LOG(LogInit, Log, TEXT("Donezo!"));
}

void AprjGameMode::SendNetworkMessage(const FString& data) const
{
	if (!connection || GetGameState<AprjGameStateBase>()->GetConnectionStatus() == EConnectionStatus::NO_CONNECTION)
	{
		UE_LOG(LogWindows, Warning, TEXT("Attempting to send the following message without a valid connection: '%s'"), *data);
		return;
	}
	UE_LOG(LogWindows, Warning, TEXT("Sending websocket message: '%s'"), *data);
	connection->SendText(data);
}

void AprjGameMode::OnOpen()
{
	UE_LOG(LogWindows, Warning, TEXT("Successfully connected"));
	GetGameState<AprjGameStateBase>()->SetConnectionStatus(EConnectionStatus::NO_SESSION);
}

void AprjGameMode::OnError(const FString& errorMessage) const
{
	UE_LOG(LogWindows, Warning, TEXT("Error inside websocket connection: '%s'"), *errorMessage);
	GetGameState<AprjGameStateBase>()->SetConnectionStatus(EConnectionStatus::NO_CONNECTION);
}

void AprjGameMode::OnClose() const
{
	UE_LOG(LogWindows, Warning, TEXT("Websocket closed"));
	GetGameState<AprjGameStateBase>()->SetConnectionStatus(EConnectionStatus::NO_CONNECTION);
}

void AprjGameMode::OnMessage(const FString& data)
{
	UE_LOG(LogWindows, Warning, TEXT("Received websocket data: '%s'"), *data);

	// convert text to json object we can traverse
	FString tmpData = data;
	TSharedRef<TJsonReader<TCHAR>> Reader = FJsonStringReader::Create(MoveTemp(tmpData));

	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogWindows, Warning, TEXT("Unable to parse json: '%s'"), *data);
		return;
	}

	const FString command = JsonObject->GetStringField("command");
	UCommand* commandObject = Cast<UCommand>(UWebSocketBlueprintLibrary::JsonToObject(data, commandMapping[command], true));
	OnCommandReceived(commandObject);
}

void AprjGameMode::OnCommandReceived(UCommand* command)
{
	UE_LOG(LogWindows, Log, TEXT("Received command: %s"), *command->ToString());
	if (command->error)
	{
		UE_DEBUG_BREAK();
		return;
	}

	if (command->command == "sessionJoin")
	{
		USessionJoin* sessionJoin = Cast<USessionJoin>(command);

		AprjGameStateBase* gameState = GetGameState<AprjGameStateBase>();
		gameState->SetConnectionStatus(EConnectionStatus::IN_SESSION);
		gameState->SessionID = sessionJoin->sessionID;
		gameState->LocalPlayerID = sessionJoin->playerID;
		gameState->CurrentSession = sessionJoin->session;

		SpawnPlayerByID(true, sessionJoin->playerID, sessionJoin->player);
	}

	if (command->command == "sessionLeave")
	{
		AprjGameStateBase* gameState = GetGameState<AprjGameStateBase>();
		gameState->SetConnectionStatus(EConnectionStatus::NO_SESSION);
		ResetLevel();
	}

	if (command->command == "playerJoin")
	{
		UPlayerJoin* playerJoin = Cast<UPlayerJoin>(command);

		SpawnPlayerByID(false, playerJoin->playerID, playerJoin->player);
	}
}

void AprjGameMode::SpawnPlayerByID(bool isLocalPlayer, int32 playerID, UPlayerData* playerData)
{
	UE_LOG(LogExec, Log, TEXT("Spawning %s player: ID: %d"), isLocalPlayer ? "local" : "remote", playerID);
	APlayerController* playerController(
		isLocalPlayer ?
		GetWorld()->GetFirstPlayerController() :
		GetWorld()->SpawnActor<APlayerController>(RemotePlayerControllerClass, this->GetRootComponent()->GetComponentTransform())
	);

	AprjPlayerState* state(Cast<AprjPlayerState>(playerController->PlayerState));
	state->networkPlayerID = playerID;
	state->networkPlayerData = playerData;
	APawn* pawn(GetWorld()->SpawnActor<APawn>(IngamePawnClass, FTransform(FRotator(), FindPlayerStart(playerController, playerData->name)->GetRootComponent()->GetComponentLocation())));

	playerController->Possess(pawn);
}

void AprjGameMode::RemovePlayerByID(int32 playerID)
{

}

void AprjGameMode::ConnectToServer(const FString& hostname, uint32 port)
{
	FString URI = hostname + ":" + FString::FromInt(port);

	UE_LOG(LogExec, Log, TEXT("Connecting to %s"), *URI);

	connection = UWebSocketBlueprintLibrary::Connect(URI);

	FScriptDelegate OnConnectDelegate;
	OnConnectDelegate.BindUFunction(this, "OnOpen");
	connection->OnConnectComplete.Add(OnConnectDelegate);

	FScriptDelegate OnCloseDelegate;
	OnCloseDelegate.BindUFunction(this, "OnClose");
	connection->OnClosed.Add(OnCloseDelegate);

	FScriptDelegate OnErrorDelegate;
	OnErrorDelegate.BindUFunction(this, "OnError");
	connection->OnConnectError.Add(OnErrorDelegate);

	FScriptDelegate OnMessageDelegate;
	OnMessageDelegate.BindUFunction(this, "OnMessage");
	connection->OnReceiveData.Add(OnMessageDelegate);
}

AprjGameMode::AprjGameMode()
	: Super()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ALocalPlayerController::StaticClass();
	RemotePlayerControllerClass = ARemotePlayerController::StaticClass();
	IngamePawnClass = AprjPawn::StaticClass();
	PlayerStateClass = AprjPlayerState::StaticClass();
	GameStateClass = AprjGameStateBase::StaticClass();
	HUDClass = AprjHUD::StaticClass();

	commandMapping.Add("sessionJoin",	 USessionJoin::StaticClass());
	commandMapping.Add("sessionUpdate",	 USessionUpdate::StaticClass());
	commandMapping.Add("sessionLeave",	 USessionLeave::StaticClass());
	commandMapping.Add("playerJoin",	 UPlayerJoin::StaticClass());
	commandMapping.Add("playerUpdate",	 UPlayerUpdate::StaticClass());
}


// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "prjGameMode.h"
#include "prjPawn.h"

#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

#include "prjGameStateBase.h"

#include "DataFormats/Request/CreateSession.h"
#include "DataFormats/Response/SessionJoin.h"
#include "DataFormats/Response/SessionUpdate.h"
#include "DataFormats/Response/SessionLeave.h"
#include "DataFormats/Response/PlayerJoin.h"
#include "DataFormats/Response/PlayerUpdate.h"
#include "DataFormats/Request/CreateSession.h"

void AprjGameMode::StartPlay()
{
	FScriptDelegate OnMessageDelegate;
	OnMessageDelegate.BindUFunction(this, "OnCommandReceived");
	this->OnWebsocketCommand.Add(OnMessageDelegate);
	UE_LOG(LogInit, Log, TEXT("Donezo!"));
	this->OnWebsocketCommand.Broadcast(nullptr);
}

void AprjGameMode::SendNetworkMessage(const FString& data) const
{
	if (!connection)
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

	FString resultString;
	UWebSocketBlueprintLibrary::ObjectToJson(UCreateSession::Create(USessionData::Create("Sand Castle", 3 * 60 * 1000, 12345), UPlayerData::Create("UE4 Player", 1.0f, 2.0f, 0x3F7AF3)), resultString);
	SendNetworkMessage(resultString);
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
	UE_LOG(LogInit, Log, TEXT("Command received!"));
	if (USessionJoin* sessionJoin = Cast<USessionJoin>(command))
	{
		UE_LOG(LogWindows, Warning, TEXT("Received join: sessionID: %d, x: %f, y: %f"), sessionJoin->sessionID, sessionJoin->player->position->GetX(), sessionJoin->player->position->GetY());
	}
	else if (USessionUpdate* sessionUpdate = Cast<USessionUpdate>(command))
	{
		UE_LOG(LogWindows, Warning, TEXT("Received update: x: %f, y: %f"), sessionUpdate->player->position->GetX(), sessionUpdate->player->position->GetY());
	}
	else
	{
		UE_LOG(LogWindows, Warning, TEXT("Received unhandled command: %s"), *command->StaticClass()->GetFullName());
	}
}


void AprjGameMode::ConnectToServer(FString hostname, uint32 port)
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
{
	// set default pawn class to our character class
	DefaultPawnClass = AprjGameMode::StaticClass();

	commandMapping.Add("sessionJoin",	 USessionJoin::StaticClass());
	commandMapping.Add("sessionUpdate",	 USessionUpdate::StaticClass());
	commandMapping.Add("sessionLeave",	 USessionLeave::StaticClass());
	commandMapping.Add("playerJoin",	 UPlayerJoin::StaticClass());
	commandMapping.Add("playerUpdate",	 UPlayerUpdate::StaticClass());
}


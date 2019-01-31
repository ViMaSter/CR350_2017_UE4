// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "prjGameMode.h"
#include "prjPawn.h"

#include "WebSocketBlueprintLibrary.h"

#include "UObject/WeakObjectPtr.h"

#include "Session.h"


AprjGameMode::AprjGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AprjPawn::StaticClass();
}

void AprjGameMode::ConnectToServer(const FString& hostname, int port)
{
	connection = UWebSocketBlueprintLibrary::Connect(FString::Printf(TEXT("ws://%s:%d"), *hostname, port));

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

void AprjGameMode::SendMessage(const FString& message)
{
	connection->SendText(message);
}

void AprjGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AprjGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AprjGameMode::OnOpen()
{
	isConnected = true;
}

void AprjGameMode::OnClose()
{
	isConnected = false;
}

void AprjGameMode::OnError(const FString& errorMessage)
{
	UE_LOG(LogWindows, Error, TEXT("Error occured inside websocket connection: %s"), *errorMessage);
}

void AprjGameMode::OnMessage(const FString& data)
{
	UE_LOG(LogWindows, Warning, TEXT("Received network message: %s"), *data);

	FString modifiableCopy = data;

	TSharedRef<TJsonReader<TCHAR>> Reader = FJsonStringReader::Create(MoveTemp(modifiableCopy));

	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogWindows, Warning, TEXT("Unable to parse json: '%s'"), *data);
		return;
	}

	const FString command = JsonObject->GetStringField("command");
	if (command == "sessionJoin")
	{
		session = NewObject<USession>();
		session->playerID = JsonObject->GetIntegerField("playerID");
		session->sessionID = JsonObject->GetIntegerField("sessionID");
	}
}


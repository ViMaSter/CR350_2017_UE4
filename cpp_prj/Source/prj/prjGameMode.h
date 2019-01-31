// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "prjGameMode.generated.h"


UCLASS(MinimalAPI)
class AprjGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AprjGameMode();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void BeginPlay() override;

private:

	// Websocket related members
	bool isConnected = false;
	class UWebSocketBase* connection;

	// Client -> Server communication
	UFUNCTION(BlueprintCallable)
	void ConnectToServer(const FString& hostname, int port);
	UFUNCTION(BlueprintCallable)
	void SendMessage(const FString& message);

	// Server -> Client communication
	UFUNCTION()
	void OnOpen();
	UFUNCTION()
	void OnClose();
	UFUNCTION()
	void OnError(const FString& errorMessage);
	UFUNCTION()
	void OnMessage(const FString& data);

	// Session related members
	class USession* session = nullptr;
};




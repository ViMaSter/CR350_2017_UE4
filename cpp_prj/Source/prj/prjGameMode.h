// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Delegates/DelegateCombinations.h"

#include "DataFormats/PlayerData.h"
#include "DataFormats/Command.h"

#include "WebSocketBlueprintLibrary.h"

#include "prjGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCommandReceivedSignature, UCommand*, command );

UCLASS(MinimalAPI)
class AprjGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// UE4 core
	virtual void StartPlay() override;

	// Websocket related-methods
	UFUNCTION()
	virtual void OnOpen();
	UFUNCTION()
	virtual void OnClose() const;
	UFUNCTION()
	virtual void OnError(const FString& errorMessage) const;
	UFUNCTION()
	virtual void OnMessage(const FString& data);
	UFUNCTION()
	void OnCommandReceived(UCommand* command);

	class UWebSocketBase* connection;
	TMap<int32, UPlayerData> spawningQueue;
	TMap<FString, UClass*> commandMapping;

public:
	AprjGameMode();

	// Websocket related-methods
	void SendNetworkMessage(const FString& data) const;
	void ConnectToServer(FString hostname, uint32 port);

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
	FOnCommandReceivedSignature OnWebsocketCommand;
};




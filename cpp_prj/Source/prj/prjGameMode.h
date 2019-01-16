// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Delegates/DelegateCombinations.h"

#include "prjPawn.h"

#include "prjGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCommandReceivedSignature, class UCommand*, command );

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
	void OnCommandReceived(class UCommand* command);
	void SpawnPlayerByID(bool isLocalPlayer, int32 playerID, class UPlayerData* playerData);
	void RemovePlayerByID(int32 playerID);

	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	class UWebSocketBase* connection = nullptr;
	TMap<int32, class UPlayerData*> spawningQueue;
	TMap<FString, UClass*> commandMapping;

public:
	AprjGameMode();

	// Websocket related-methods
	void SendNetworkMessage(const FString& data) const;
	void ConnectToServer(const FString& hostname, uint32 port);

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
	FOnCommandReceivedSignature OnWebsocketCommand;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<APlayerController> RemoteControllerClass;
};




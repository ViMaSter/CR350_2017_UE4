// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RemotePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API ARemotePlayerController : public APlayerController
{
	GENERATED_BODY()

	ARemotePlayerController();

	// Begin Controller Interface
	virtual void Possess(APawn* InPawn) override;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnCommandReceived(class UCommand* command);

	class AprjPlayerState* networkPlayerState = nullptr;
	class AprjPawn* networkPlayerPawn = nullptr;
	float targetX = 0.0f;
	float targetY = 0.0f;
};

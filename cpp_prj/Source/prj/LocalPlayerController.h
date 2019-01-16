// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LocalPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API ALocalPlayerController : public APlayerController
{
	GENERATED_BODY()

	ALocalPlayerController();
	virtual void BeginPlay() override;
	// Callback to allow for another network update

	virtual void Tick(float DeltaSeconds) override;

	// Checks if a network update is required and tries to send
	void AttemptToUpdateNetwork();

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;

	FTimerHandle WebUpdateTimerHandle;
	float UpdateFrequencyInSeconds = 1.0f / 30.0f; // 30hz
	bool ShouldSendUpdate = true;

public:
	UFUNCTION()
	void NetworkTickReady();
};

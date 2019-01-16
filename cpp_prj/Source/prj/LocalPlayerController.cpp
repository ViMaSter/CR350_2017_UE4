// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalPlayerController.h"
#include "prjPawn.h"

#include "prjGameMode.h"

#include "WebSocketBlueprintLibrary.h"
#include "DataFormats/Request/UpdatePlayer.h"
#include "DataFormats/PlayerData.h"

const FName ALocalPlayerController::MoveForwardBinding("MoveForward");
const FName ALocalPlayerController::MoveRightBinding("MoveRight");

ALocalPlayerController::ALocalPlayerController()
	: Super()
{
}

void ALocalPlayerController::BeginPlay()
{
	EnableInput(this);

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);

	FTimerDynamicDelegate NetworkTickDelegate;
	NetworkTickDelegate.BindUFunction(this, "NetworkTickReady");
	GetWorld()->GetTimerManager().SetTimer(WebUpdateTimerHandle, NetworkTickDelegate, UpdateFrequencyInSeconds, true);
}

void ALocalPlayerController::NetworkTickReady()
{
	ShouldSendUpdate = true;
}

void ALocalPlayerController::Tick(float DeltaSeconds)
{
	if (!GetPawn())
	{
		return;
	}

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	Cast<AprjPawn>(GetPawn())->SetMovement(RightValue, ForwardValue);

	AttemptToUpdateNetwork();
}

void ALocalPlayerController::AttemptToUpdateNetwork()
{
	// Have we sent an update too recently?
	if (!ShouldSendUpdate)
	{
		return;
	}

	// Are we moving?
	if (FMath::IsNearlyEqual(GetInputAxisValue(MoveForwardBinding), 0.0f) && FMath::IsNearlyEqual(GetInputAxisValue(MoveRightBinding), 0.0f))
	{
		return;
	}

	// Construct network message
	FString resultString;
	UWebSocketBlueprintLibrary::ObjectToJson(UUpdatePlayer::Create(UPlayerData::Create("UE4 Player", GetPawn()->GetActorLocation().Y / 100.0f, GetPawn()->GetActorLocation().X / 100.0f, 0x3F7AF3)), resultString);
	GetWorld()->GetAuthGameMode<AprjGameMode>()->SendNetworkMessage(resultString);

	// Set flag to prevent too rapid of an update
	ShouldSendUpdate = false;
}
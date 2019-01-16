// Fill out your copyright notice in the Description page of Project Settings.

#include "RemotePlayerController.h"

#include "prjGameMode.h"
#include "prjPawn.h"
#include "prjPlayerState.h"
#include "DataFormats/LowercaseVector2D.h"

#include "DataFormats/Response/PlayerUpdate.h"

ARemotePlayerController::ARemotePlayerController()
	: Super()
{
}


void ARemotePlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
		
	// initialize often-used references
	networkPlayerState = Cast<AprjPlayerState>(PlayerState);
	networkPlayerPawn = Cast<AprjPawn>(GetPawn());

	// listen to network messages
	FScriptDelegate OnMessageDelegate;
	OnMessageDelegate.BindUFunction(this, "OnCommandReceived");
	GetWorld()->GetAuthGameMode<AprjGameMode>()->OnWebsocketCommand.Add(OnMessageDelegate);

	// default initialize targetPositions
	FVector pawnPosition = InPawn->GetActorLocation();
	targetX = pawnPosition.X;
	targetY = pawnPosition.Y;
}


void ARemotePlayerController::Tick(float DeltaSeconds)
{
	if (!GetPawn())
	{
		return;
	}

	FVector pawnPosition = GetPawn()->GetActorLocation();

	float deltaX = FMath::Abs(targetX - pawnPosition.X);
	float deltaY = FMath::Abs(targetY - pawnPosition.Y);
	if (FMath::IsNearlyEqual(targetX, pawnPosition.X))
	{
		deltaX = 0;
	}
	if (FMath::IsNearlyEqual(targetY, pawnPosition.Y))
	{
		deltaY = 0;
	}

	networkPlayerPawn->SetMovement(deltaX, deltaY);
}

void ARemotePlayerController::OnCommandReceived(class UCommand* command)
{
	if (command->command == "playerUpdate")
	{
		UPlayerUpdate* playerUpdate = Cast<UPlayerUpdate>(command);
		if (playerUpdate->playerID != networkPlayerState->networkPlayerID)
		{
			return;
		}

		targetX = playerUpdate->player->position->GetX();
		targetY = playerUpdate->player->position->GetY();
	}
}

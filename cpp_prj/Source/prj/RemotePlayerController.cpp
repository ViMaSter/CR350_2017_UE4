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

	float deltaX = FMath::Clamp<float>((targetX - pawnPosition.X) / 100, -1, 1);
	float deltaY = FMath::Clamp<float>((targetY - pawnPosition.Y) / 100, -1, 1);

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

		ULowercaseVector2D* positionCopy = DuplicateObject<ULowercaseVector2D>(playerUpdate->player->position, playerUpdate);
		positionCopy->ToUE4Space();

		// adjust for UE4 coordinate system
		targetY = positionCopy->GetX();
		targetX = positionCopy->GetY();
	}
}

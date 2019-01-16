// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "DataFormats/PlayerData.h"

#include "prjPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API AprjPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 networkPlayerID = -1;
	UPlayerData* networkPlayerData = nullptr;
};

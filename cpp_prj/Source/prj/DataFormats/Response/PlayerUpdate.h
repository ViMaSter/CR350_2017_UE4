// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/PlayerData.h"
#include "PlayerUpdate.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UPlayerUpdate : public UCommand
{
	GENERATED_BODY()
			
	UPlayerUpdate() {}
			
public:
	~UPlayerUpdate() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 playerID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class UPlayerData* player;
};
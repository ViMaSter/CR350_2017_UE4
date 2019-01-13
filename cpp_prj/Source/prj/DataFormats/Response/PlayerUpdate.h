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
	UPlayerData* player;

	virtual FString ToString() override
	{
		 return FString::Printf(TEXT("%s | Player ID: %d | Player [%s]"), *Super::ToString(), playerID, *player->ToString());
	}
};
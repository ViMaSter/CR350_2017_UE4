// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/PlayerData.h"
#include "PlayerJoin.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UPlayerJoin : public UCommand
{
	GENERATED_BODY()
			
	UPlayerJoin() {}
			
public:
	~UPlayerJoin() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 playerID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class UPlayerData* player;

	virtual FString ToString() override
	{
		 return FString::Printf(TEXT("%s | Player ID: %d | Player [%s]"), *Super::ToString(), player, *player->ToString());
	}
};
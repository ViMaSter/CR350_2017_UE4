// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "UpdatePlayer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UUpdatePlayer : public UCommand
{
	GENERATED_BODY()
			
	UUpdatePlayer();

public:
	~UUpdatePlayer();

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 playerID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class UPlayerData* player;

public:
	static UUpdatePlayer* Create(class UPlayerData* player);
	virtual FString ToString() override;
};
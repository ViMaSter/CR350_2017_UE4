// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "LowercaseVector2D.h"

#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UPlayerData : public UObject
{
	GENERATED_BODY()

	UPlayerData();

public:
	~UPlayerData();

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	FString name;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class ULowercaseVector2D* position;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 colorHex;

	static UPlayerData* Create(FString name, float x, float y, int32 colorHex);
};

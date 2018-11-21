// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SessionData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API USessionData : public UObject
{
	GENERATED_BODY()

public:
	USessionData();
	~USessionData();

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	float playerPositionX;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	float playerPositionY;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	float health;

	static USessionData* Create(float playerPositionX, float playerPositionY, float health);
};

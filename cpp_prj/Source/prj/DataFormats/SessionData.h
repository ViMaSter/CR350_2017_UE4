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

	USessionData() {}

public:
	~USessionData() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	FString mapName;

	// int32 due to constraints with using uint + 64-bit integers in blueprint
	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 timelimit;

	// int32 due to constraints with using uint + 64-bit integers in blueprint
	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 currentMatchStart;

	static USessionData* Create(FString mapName, int32 timelimit, int32 currentMatchStart)
	{
		USessionData* newObject(NewObject<USessionData>());
		newObject->mapName = mapName;
		newObject->timelimit = timelimit;
		newObject->currentMatchStart = currentMatchStart;
		return newObject;
	}
};

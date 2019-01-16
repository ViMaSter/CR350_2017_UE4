// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "PlayerLeave.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UPlayerLeave : public UCommand
{
	GENERATED_BODY()
			
	UPlayerLeave() {}
			
public:
	~UPlayerLeave() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 playerID;

	virtual FString ToString() override
	{
		 return FString::Printf(TEXT("%s | Player ID: %d"), *Super::ToString(), playerID);
	}
};
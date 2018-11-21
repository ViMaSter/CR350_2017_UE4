// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Command.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UCommand : public UObject
{
	GENERATED_BODY()

protected:
	UCommand() {}
		
public:
	~UCommand() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	FString command;
};

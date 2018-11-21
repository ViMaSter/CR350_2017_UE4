// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "SessionUpdate.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API USessionUpdate : public UCommand
{
	GENERATED_BODY()
			
	USessionUpdate() {}
			
public:
	~USessionUpdate() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 sessionID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class USessionData* session;
};
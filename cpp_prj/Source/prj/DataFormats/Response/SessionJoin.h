// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "SessionJoin.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API USessionJoin : public UCommand
{
	GENERATED_BODY()
			
	USessionJoin() {}
			
public:
	~USessionJoin() {}

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 sessionID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class USessionData* session;
};
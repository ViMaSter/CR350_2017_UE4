// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "UpdateSession.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UUpdateSession : public UCommand
{
	GENERATED_BODY()
			
	UUpdateSession();

public:
	~UUpdateSession();

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 sessionID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class USessionData* parameters;

public:
	static UUpdateSession* Create(int32 sessionID, USessionData* parameters);
};
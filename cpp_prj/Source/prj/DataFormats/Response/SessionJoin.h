// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"
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
	int32 playerID;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class USessionData* session;

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class UPlayerData* player;

	virtual FString ToString() override
	{
		 return FString::Printf(TEXT("%s | Session ID: %d | Player ID: %d | Session: [%s] | Player [%s]"), *Super::ToString(), sessionID, playerID, session == nullptr ? TEXT("EMPTY") : *session->ToString(), player == nullptr ? TEXT("EMPTY") : *player->ToString());
	}
};
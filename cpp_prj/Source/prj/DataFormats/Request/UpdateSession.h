// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"
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
	class USessionData* session;
	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class UPlayerData* player;

public:
	static UUpdateSession* Create(USessionData* session, UPlayerData* player);
};
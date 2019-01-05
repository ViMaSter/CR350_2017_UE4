// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"
#include "CreateSession.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UCreateSession : public UCommand
{
	GENERATED_BODY()

	UCreateSession();

public:
	~UCreateSession();

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class USessionData* session;
	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	class UPlayerData* player;

public:
	static UCreateSession* Create(USessionData* session, UPlayerData* player);
};
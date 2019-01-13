// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "JoinSession.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API UJoinSession : public UCommand
{
	GENERATED_BODY()

	UJoinSession();

public:
	~UJoinSession();

	UPROPERTY(Category = WebSocket, VisibleAnywhere, BlueprintReadOnly)
	int32 sessionID;

public:
	static UJoinSession* Create(int32 sessionID);
	virtual FString ToString() override;
};
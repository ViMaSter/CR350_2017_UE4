// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "LeaveSession.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API ULeaveSession : public UCommand
{
	GENERATED_BODY()

	ULeaveSession();

public:
	~ULeaveSession();

public:
	static ULeaveSession* Create();
};
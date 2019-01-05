// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataFormats/Command.h"
#include "DataFormats/SessionData.h"
#include "SessionLeave.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API USessionLeave : public UCommand
{
	GENERATED_BODY()
			
	USessionLeave() {}
			
public:
	~USessionLeave() {}

};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SessionJoin.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API USessionJoin : public UObject
{
	GENERATED_BODY()

public:
	FString command = "UNSET";
	int error = -1;
	int playerID = -1;
	int sessionID = -1;
};

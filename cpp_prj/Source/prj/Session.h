// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Session.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API USession : public UObject
{
	GENERATED_BODY()

public:
	int playerID = 0;
	int sessionID = 0;
};

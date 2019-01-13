// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Delegates/DelegateCombinations.h"

#include "prjGameStateBase.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EConnectionStatus : uint8
{
	NO_CONNECTION	UMETA(DisplayName = "No connection"),
	NO_SESSION		UMETA(DisplayName = "No session"),
	IN_SESSION		UMETA(DisplayName = "In session")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConnectionStatusChanged, EConnectionStatus, oldConnectionStatus, EConnectionStatus, newConnectionStatus);

/**
 * 
 */
UCLASS()
class PRJ_API AprjGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	EConnectionStatus connectionStatus;

public:
	EConnectionStatus GetConnectionStatus()
	{
		return connectionStatus;
	}
	void SetConnectionStatus(EConnectionStatus newStatus);
	FOnConnectionStatusChanged OnConnectionStatusChanged;
};

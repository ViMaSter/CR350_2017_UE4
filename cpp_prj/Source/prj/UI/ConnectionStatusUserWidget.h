// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"

#include "prjGameStateBase.h"

#include "ConnectionStatusUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API UConnectionStatusUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UConnectionStatusUserWidget(const FObjectInitializer& ObjectInitializer, EConnectionStatus activeDuringStatus);
private:
	UConnectionStatusUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

private:
	UFUNCTION()
	void OnConnectionStatusChanged(EConnectionStatus newStatus);
	void UpdateVisibility(bool shown);

public:
	UPROPERTY(Category = Websocket, BlueprintReadWrite, EditAnywhere)
	EConnectionStatus activeDuringStatus;
};

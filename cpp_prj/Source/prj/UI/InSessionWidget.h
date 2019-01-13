// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ConnectionStatusUserWidget.h"

#include "InSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API UInSessionWidget : public UConnectionStatusUserWidget
{
	GENERATED_BODY()
protected:
	UInSessionWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	UFUNCTION()
	void LeaveSession();


public:
	// User-exposed config of styling
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	int ButtonHeight = 500;
};

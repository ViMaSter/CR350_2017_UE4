// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ConnectionStatusUserWidget.h"

#include "NoConnectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API UNoConnectionWidget : public UConnectionStatusUserWidget
{
	GENERATED_BODY()
protected:
	UNoConnectionWidget(const FObjectInitializer& ObjectInitializer);
};

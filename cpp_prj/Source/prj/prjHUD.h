// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "prjHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API AprjHUD : public AHUD
{
	GENERATED_BODY()

	virtual void PostInitializeComponents() override;

	void DoThing();
	
	class UNoConnectionWidget* noConnectionWidget;
};

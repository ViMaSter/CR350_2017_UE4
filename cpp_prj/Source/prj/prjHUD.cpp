// Fill out your copyright notice in the Description page of Project Settings.

#include "prjHUD.h"
#include "UI/NoConnectionWidget.h"
#include "UI/NoSessionWidget.h"
#include "UI/InSessionWidget.h"

void AprjHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	noConnectionWidget = CreateWidget<UNoConnectionWidget>(GetOwningPlayerController(), UNoConnectionWidget::StaticClass());
	noSessionWidget = CreateWidget<UNoSessionWidget>(GetOwningPlayerController(), UNoSessionWidget::StaticClass());
	inSessionWidget = CreateWidget<UInSessionWidget>(GetOwningPlayerController(), UInSessionWidget::StaticClass());

	if (noConnectionWidget)
	{
		noConnectionWidget->AddToViewport();
	}
	if (noSessionWidget)
	{
		noSessionWidget->AddToViewport();
	}
	if (inSessionWidget)
	{
		inSessionWidget->AddToViewport();
	}
}


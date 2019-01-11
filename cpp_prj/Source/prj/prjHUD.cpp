// Fill out your copyright notice in the Description page of Project Settings.

#include "prjHUD.h"
#include "UI/NoConnectionWidget.h"

void AprjHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Create the widget and store it.
	noConnectionWidget = CreateWidget<UNoConnectionWidget>(GetOwningPlayerController(), UNoConnectionWidget::StaticClass());

	// now you can use the widget directly since you have a referance for it.
	// Extra check to  make sure the pointer holds the widget.
	if (noConnectionWidget)
	{
		//let add it to the view port
		noConnectionWidget->AddToViewport();
	}
}

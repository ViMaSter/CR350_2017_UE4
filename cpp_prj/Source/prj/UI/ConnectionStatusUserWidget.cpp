// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectionStatusUserWidget.h"
#include "SlateWrapperTypes.h"
#include "prjGameStateBase.h"
#include "Engine/World.h"
#include "Components/Widget.h"
#include "WidgetTree.h"

UConnectionStatusUserWidget::UConnectionStatusUserWidget(const FObjectInitializer& ObjectInitializer, EConnectionStatus activeDuringStatus)
	: Super(ObjectInitializer)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode() || !GetWorld()->GetAuthGameMode()->GetGameState<AprjGameStateBase>())
	{
		return;
	}
	
	AprjGameStateBase* gameState = GetWorld()->GetAuthGameMode()->GetGameState<AprjGameStateBase>();
	FScriptDelegate OnConnectionStatusChangedDelegate;
	OnConnectionStatusChangedDelegate.BindUFunction(this, "OnConnectionStatusChanged");

	gameState->OnConnectionStatusChanged.Add(OnConnectionStatusChangedDelegate);
	UpdateVisibility(gameState->GetConnectionStatus() == activeDuringStatus);
}

void UConnectionStatusUserWidget::OnConnectionStatusChanged(EConnectionStatus newStatus)
{
	UpdateVisibility(newStatus == activeDuringStatus);
}

void UConnectionStatusUserWidget::UpdateVisibility(bool shown)
{
	this->SetVisibility(shown ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

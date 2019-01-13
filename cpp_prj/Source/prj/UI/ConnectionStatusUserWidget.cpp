// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectionStatusUserWidget.h"
#include "SlateWrapperTypes.h"
#include "prjGameStateBase.h"
#include "Engine/World.h"
#include "Components/Widget.h"
#include "WidgetTree.h"

UConnectionStatusUserWidget::UConnectionStatusUserWidget(const FObjectInitializer& ObjectInitializer, EConnectionStatus activeDuringStatus)
	: Super(ObjectInitializer)
	, activeDuringStatus(activeDuringStatus)
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

void UConnectionStatusUserWidget::OnConnectionStatusChanged(EConnectionStatus oldStatus, EConnectionStatus newStatus)
{
	UpdateVisibility(newStatus == activeDuringStatus);
}

void UConnectionStatusUserWidget::UpdateVisibility(bool shown)
{
	this->SetVisibility(shown ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}


TSharedRef<SWidget> UConnectionStatusUserWidget::RebuildWidget()
{
	AprjGameStateBase* gameState = GetWorld()->GetAuthGameMode()->GetGameState<AprjGameStateBase>();
	OnConnectionStatusChanged(EConnectionStatus::NO_CONNECTION, gameState->GetConnectionStatus());
	return Super::RebuildWidget();
}
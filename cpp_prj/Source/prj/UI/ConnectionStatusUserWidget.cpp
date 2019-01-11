// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectionStatusUserWidget.h"
#include "SlateWrapperTypes.h"
#include "prjGameStateBase.h"
#include "Engine/World.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

UConnectionStatusUserWidget::UConnectionStatusUserWidget(const FObjectInitializer& ObjectInitializer)
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

TSharedRef<SWidget> UConnectionStatusUserWidget::RebuildWidget()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!RootWidget)
	{
		RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), (TEXT("Root")));
		UCanvasPanelSlot *RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);
		WidgetTree->RootWidget = RootWidget;
	}

	UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
	button->SetColorAndOpacity(FLinearColor(0, 0, 0, 0));

	// add it to child of root
	UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
	UPanelSlot* slot = root->AddChild(button);
	UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

	// set position and stuff
	canvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
	canvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	canvasSlot->SetOffsets(FMargin(0, 0, 500, 500));

	return Super::RebuildWidget();
}

void UConnectionStatusUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind delegates here.
}
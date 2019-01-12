// Fill out your copyright notice in the Description page of Project Settings.

#include "NoConnectionWidget.h"

#include "Engine.h"

#include "WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "prjGameMode.h"

UNoConnectionWidget::UNoConnectionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer, EConnectionStatus::NO_CONNECTION)
{

}

TSharedRef<SWidget> UNoConnectionWidget::RebuildWidget()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!RootWidget)
	{
		RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), (TEXT("Root")));
		UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);
		WidgetTree->RootWidget = RootWidget;
	}

	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	// Create two buttons - local and remote server connection requests
	{
		UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		button->SetColorAndOpacity(FLinearColor(0, 0, 0));

		UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		textBlock->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 1)));
		textBlock->SetText(FText::FromString("Connect to local server"));
		button->OnClicked.AddDynamic(this, &UNoConnectionWidget::ConnectToLocalServer);
		button->AddChild(textBlock);


		UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
		UPanelSlot* slot = root->AddChild(button);
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

		canvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.5f, 0.0f));
		canvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
		canvasSlot->SetOffsets(FMargin(0, 0, 0, ButtonHeight));
	}

	{
		UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		button->SetColorAndOpacity(FLinearColor(0, 0, 0));

		UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());;
		textBlock->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 1)));
		textBlock->SetText(FText::FromString("Connect to remote server"));
		button->OnClicked.AddDynamic(this, &UNoConnectionWidget::ConnectToRemoteServer);
		button->AddChild(textBlock);

		UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
		UPanelSlot* slot = root->AddChild(button);
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

		canvasSlot->SetAnchors(FAnchors(0.5f, 0.0f, 1.0f, 0.0f));
		canvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
		canvasSlot->SetOffsets(FMargin(0, 0, 0, ButtonHeight));
	}

	return Super::RebuildWidget();
}

void UNoConnectionWidget::ConnectToLocalServer()
{
	ConnectToServer(LocalHostname, LocalPort);
}

void UNoConnectionWidget::ConnectToRemoteServer()
{
	ConnectToServer(RemoteHostname, RemotePort);
}

void UNoConnectionWidget::ConnectToServer(FString hostname, uint32 port)
{
	Cast<AprjGameMode>(GetWorld()->GetAuthGameMode())->ConnectToServer(FString("ws://") + hostname, port);
}
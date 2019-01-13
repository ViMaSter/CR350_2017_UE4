// Fill out your copyright notice in the Description page of Project Settings.

#include "InSessionWidget.h"

#include "WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "WebSocketBlueprintLibrary.h"

#include "DataFormats/Request/LeaveSession.h"

#include "prjGameMode.h"

UInSessionWidget::UInSessionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer, EConnectionStatus::IN_SESSION)
{

}

TSharedRef<SWidget> UInSessionWidget::RebuildWidget()
{
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!RootWidget)
	{
		RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), (TEXT("Root")));
		UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);
		WidgetTree->RootWidget = RootWidget;
	}

	{
		UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		button->SetColorAndOpacity(FLinearColor(0, 0, 0));

		UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		textBlock->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 1)));
		textBlock->SetText(FText::FromString("Leave session"));
		button->OnClicked.AddDynamic(this, &UInSessionWidget::LeaveSession);
		button->AddChild(textBlock);


		UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
		UPanelSlot* slot = root->AddChild(button);
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

		canvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.5f, 0.0f));
		canvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
		canvasSlot->SetOffsets(FMargin(0, 0, 0, ButtonHeight));
	}

	return Super::RebuildWidget();
}

void UInSessionWidget::LeaveSession()
{
	FString resultString;
	UWebSocketBlueprintLibrary::ObjectToJson(ULeaveSession::Create(), resultString);
	GetWorld()->GetAuthGameMode<AprjGameMode>()->SendNetworkMessage(resultString);
}
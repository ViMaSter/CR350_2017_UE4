// Fill out your copyright notice in the Description page of Project Settings.

#include "NoSessionWidget.h"

#include "WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "WebSocketBlueprintLibrary.h"

#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"
#include "DataFormats/Request/CreateSession.h"
#include "DataFormats/Request/JoinSession.h"

#include "prjGameMode.h"

UNoSessionWidget::UNoSessionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer, EConnectionStatus::NO_SESSION)
{

}

TSharedRef<SWidget> UNoSessionWidget::RebuildWidget()
{
	Super::RebuildWidget();

	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

	if (!RootWidget)
	{
		RootWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), (TEXT("Root")));
		UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootWidget->Slot);
		WidgetTree->RootWidget = RootWidget;
	}

	// CreateSession button
	{
		UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
		button->SetColorAndOpacity(FLinearColor(0, 0, 0));

		UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		textBlock->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 1)));
		textBlock->SetText(FText::FromString("CreateSession"));
		button->OnClicked.AddDynamic(this, &UNoSessionWidget::FormulateCreateSessionRequest);
		button->AddChild(textBlock);


		UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
		UPanelSlot* slot = root->AddChild(button);
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

		canvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 0.5f, 0.0f));
		canvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
		canvasSlot->SetOffsets(FMargin(0, 0, 0, ButtonHeight));
	}

	// JoinSession
	{
		// button
		{
			UButton* button = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
			button->SetColorAndOpacity(FLinearColor(0, 0, 0));

			UTextBlock* textBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			textBlock->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 1)));
			textBlock->SetText(FText::FromString("Join session"));
			button->OnClicked.AddDynamic(this, &UNoSessionWidget::FormulateJoinSessionRequest);
			button->AddChild(textBlock);


			UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
			UPanelSlot* slot = root->AddChild(button);
			UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

			canvasSlot->SetAnchors(FAnchors(0.5f, 0.0f, 1.0f, 0.0f));
			canvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			canvasSlot->SetOffsets(FMargin(0, 0, 0, ButtonHeight));
		}

		// sessionID textBox
		{
			sessionIDInput = WidgetTree->ConstructWidget<UEditableTextBox>(UEditableTextBox::StaticClass());
			sessionIDInput->WidgetStyle.SetBackgroundColor(FSlateColor(FLinearColor(1, 1, 1)));
			sessionIDInput->WidgetStyle.SetForegroundColor(FSlateColor(FLinearColor(0, 0, 0)));
			sessionIDInput->WidgetStyle.SetFont("Roboto", 58);
			sessionIDInput->SetText(FText::FromString("-1"));
			UPanelWidget* root = Cast<UPanelWidget>(GetRootWidget());
			UPanelSlot* slot = root->AddChild(sessionIDInput);
			UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

			canvasSlot->SetAnchors(FAnchors(0.5f, 0.0f, 1.0f, 0.0f));
			canvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			canvasSlot->SetOffsets(FMargin(0, ButtonHeight, 0, ButtonHeight));
		}
	}

	return Super::RebuildWidget();
}

void UNoSessionWidget::FormulateCreateSessionRequest()
{
	CreateSession(
		USessionData::Create("Sand Castle", 3 * 60 * 1000, 12345),
		UPlayerData::Create("UE4 Player", 1.0f, 2.0f, 0x3F7AF3)
	);
}

void UNoSessionWidget::CreateSession(USessionData* sessionData, UPlayerData* playerData)
{
	FString resultString;
	UWebSocketBlueprintLibrary::ObjectToJson(UCreateSession::Create(sessionData, playerData), resultString);
	GetWorld()->GetAuthGameMode<AprjGameMode>()->SendNetworkMessage(resultString);
}

void UNoSessionWidget::FormulateJoinSessionRequest()
{
	JoinSession(FCString::Atoi(*sessionIDInput->GetText().ToString()));
}

void UNoSessionWidget::JoinSession(int32 sessionID)
{
	FString resultString;
	UWebSocketBlueprintLibrary::ObjectToJson(UJoinSession::Create(sessionID), resultString);
	GetWorld()->GetAuthGameMode<AprjGameMode>()->SendNetworkMessage(resultString);

	Cast<AprjGameMode>(GetWorld()->GetAuthGameMode())->SendNetworkMessage(resultString);
}
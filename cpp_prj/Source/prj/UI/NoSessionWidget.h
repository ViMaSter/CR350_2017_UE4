// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ConnectionStatusUserWidget.h"

#include "NoSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API UNoSessionWidget : public UConnectionStatusUserWidget
{
	GENERATED_BODY()
protected:
	UNoSessionWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	UFUNCTION()
	void FormulateCreateSessionRequest();
	void CreateSession(class USessionData* sessionData, class UPlayerData* playerData);

	UFUNCTION()
	void FormulateJoinSessionRequest();
	void JoinSession(int32 sessionID);

public:
	// User-exposed config of styling
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	int ButtonHeight = 500;

	class UEditableTextBox* sessionIDInput = nullptr;
};

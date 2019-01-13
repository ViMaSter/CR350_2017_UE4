// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ConnectionStatusUserWidget.h"

#include "NoConnectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRJ_API UNoConnectionWidget : public UConnectionStatusUserWidget
{
	GENERATED_BODY()
protected:
	UNoConnectionWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	UFUNCTION()
	void ConnectToLocalServer();
	UFUNCTION()
	void ConnectToRemoteServer();

	void ConnectToServer(FString hostname, uint32 port);

public:
	// User-exposed config of styling
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	int ButtonHeight = 500;

	// User-exposed config of servers
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	FString RemoteHostname = "cr350server.herokuapp.com";
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	int RemotePort = 80;
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	FString LocalHostname = "127.0.0.1";
	UPROPERTY(Category = Websocket, EditAnywhere, BlueprintReadWrite)
	int LocalPort = 500;
};

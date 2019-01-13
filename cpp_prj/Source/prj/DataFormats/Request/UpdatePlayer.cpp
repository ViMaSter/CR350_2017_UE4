// Fill out your copyright notice in the Description page of Project Settings.

#include "UpdatePlayer.h"
#include "DataFormats/PlayerData.h"

/**
 * 
 */
UUpdatePlayer::UUpdatePlayer()
{
	this->command = "updatePlayer";
}

UUpdatePlayer::~UUpdatePlayer()
{
	// intentionally void
}

UUpdatePlayer* UUpdatePlayer::Create(UPlayerData* player)
{
	UUpdatePlayer* UpdatePlayerObject(NewObject<UUpdatePlayer>());
	UpdatePlayerObject->player = player;
	return UpdatePlayerObject;
}

FString UUpdatePlayer::ToString()
{
	return FString::Printf(TEXT("%s | Player [%s]"), *Super::ToString(), *player->ToString());
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "UpdatePlayer.h"

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
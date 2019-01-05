// Fill out your copyright notice in the Description page of Project Settings.

#include "UpdateSession.h"

/**
 * 
 */
UUpdateSession::UUpdateSession()
{
	this->command = "updateSession";
}

UUpdateSession::~UUpdateSession()
{
	// intentionally void
}

UUpdateSession* UUpdateSession::Create(USessionData* session, UPlayerData* player)
{
	UUpdateSession* updateSessionObject(NewObject<UUpdateSession>());
	updateSessionObject->session = session;
	updateSessionObject->player = player;
	return updateSessionObject;
}
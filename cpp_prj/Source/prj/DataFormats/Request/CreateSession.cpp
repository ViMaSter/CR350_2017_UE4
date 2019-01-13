// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateSession.h"

#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"

/**
 * 
 */
UCreateSession::UCreateSession()
{
	this->command = "createSession";
}

UCreateSession::~UCreateSession()
{
	// intentionally void
}

UCreateSession* UCreateSession::Create(USessionData* session, UPlayerData* player)
{
	UCreateSession* createSessionObject(NewObject<UCreateSession>());
	createSessionObject->session = session;
	createSessionObject->player = player;
	return createSessionObject;
}

FString UCreateSession::ToString()
{
	return FString::Printf(TEXT("%s | Session: [%s] | Player [%s]"), *Super::ToString(), *session->ToString(), *player->ToString());
}
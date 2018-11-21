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

UUpdateSession* UUpdateSession::Create(int32 sessionID, USessionData* parameters)
{
	UUpdateSession* updateSessionObject(NewObject<UUpdateSession>());
	updateSessionObject->sessionID = sessionID;
	updateSessionObject->parameters = parameters;
	return updateSessionObject;
}
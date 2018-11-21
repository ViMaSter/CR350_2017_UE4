// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateSession.h"

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

UCreateSession* UCreateSession::Create(USessionData* parameters)
{
	UCreateSession* createSessionObject(NewObject<UCreateSession>());
	createSessionObject->parameters = parameters;
	return createSessionObject;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "JoinSession.h"

/**
 * 
 */
UJoinSession::UJoinSession()
{
	this->command = "joinSession";
}

UJoinSession::~UJoinSession()
{
	// intentionally void
}

UJoinSession* UJoinSession::Create(int32 sessionID)
{
	UJoinSession* JoinSessionObject(NewObject<UJoinSession>());
	JoinSessionObject->sessionID = sessionID;
	return JoinSessionObject;
}

FString UJoinSession::ToString()
{
	return FString::Printf(TEXT("%s | Session ID: %d"), *Super::ToString(), sessionID);
}
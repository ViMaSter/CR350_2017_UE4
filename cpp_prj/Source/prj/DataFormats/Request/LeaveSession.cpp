// Fill out your copyright notice in the Description page of Project Settings.

#include "LeaveSession.h"

/**
 * 
 */
ULeaveSession::ULeaveSession()
{
	this->command = "leaveSession";
}

ULeaveSession::~ULeaveSession()
{
	// intentionally void
}

ULeaveSession* ULeaveSession::Create()
{
	ULeaveSession* LeaveSessionObject(NewObject<ULeaveSession>());
	return LeaveSessionObject;
}
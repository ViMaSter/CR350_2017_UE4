// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SessionData.h"

/**
 * 
 */
USessionData::USessionData()
{
	// intentionally void
}
	
USessionData::~USessionData()
{
	// intentionally void
}

USessionData* USessionData::Create(float playerPositionX, float playerPositionY, float health)
{
	USessionData* newObject(NewObject<USessionData>());
	newObject->playerPositionX = playerPositionX;
	newObject->playerPositionY = playerPositionY;
	newObject->health = health;
	return newObject;
}
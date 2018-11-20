// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "prjGameMode.h"
#include "prjPawn.h"

AprjGameMode::AprjGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AprjPawn::StaticClass();
}


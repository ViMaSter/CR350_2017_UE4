#include "SessionData.h"

USessionData::USessionData() {}

USessionData::~USessionData() {}

USessionData * USessionData::Create(FString mapName, int32 timelimit, int32 currentMatchStart)
{
	USessionData* newObject(NewObject<USessionData>());
	newObject->mapName = mapName;
	newObject->timelimit = timelimit;
	newObject->currentMatchStart = currentMatchStart;
	return newObject;
}

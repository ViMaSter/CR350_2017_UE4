#include "SessionData.h"

USessionData::USessionData() {}

USessionData::~USessionData() {}

USessionData* USessionData::Create(FString mapName, int32 timelimit, int32 currentMatchStart)
{
	USessionData* newObject(NewObject<USessionData>());
	newObject->mapName = mapName;
	newObject->timelimit = timelimit;
	newObject->currentMatchStart = currentMatchStart;
	return newObject;
}

FString USessionData::ToString()
{
	return FString::Printf(TEXT("Name: %s | Position: %d | Color: %d"), *this->mapName, this->timelimit, this->currentMatchStart);
}
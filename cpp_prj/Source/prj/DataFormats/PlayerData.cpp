#include "PlayerData.h"

UPlayerData::UPlayerData() {}

UPlayerData::~UPlayerData() {}

UPlayerData* UPlayerData::Create(FString name, float x, float y, int32 colorHex)
{
	UPlayerData* newObject(NewObject<UPlayerData>());
	newObject->name = name;
	newObject->position = ULowercaseVector2D::Create(x, y);
	newObject->colorHex = colorHex;
	return newObject;
}

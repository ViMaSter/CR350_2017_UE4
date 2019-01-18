// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"

#include "LowercaseVector2D.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PRJ_API ULowercaseVector2D : public UObject
{
	GENERATED_BODY()

	ULowercaseVector2D() {}

	UPROPERTY()
	float x;
	UPROPERTY()
	float y;

public:
	~ULowercaseVector2D() {}

	UFUNCTION(Category = Websocket)
	float GetX() { return x; }
	UFUNCTION(Category = Websocket)
	float GetY() { return y; }

	const float SERVER_SPACE_SCALE = 100;

	// see http://www.cplusplus.com/forum/beginner/7469/#msg34877
	inline void ToServerSpace()
	{
		this->x = this->x / SERVER_SPACE_SCALE;
		this->y = this->y / SERVER_SPACE_SCALE;
	}

	// see http://www.cplusplus.com/forum/beginner/7469/#msg34877
	inline void ToUE4Space()
	{
		this->x = this->x * SERVER_SPACE_SCALE;
		this->y = this->y * SERVER_SPACE_SCALE;
	}
	
	static ULowercaseVector2D* Create(float x, float y)
	{
		ULowercaseVector2D* newObject(NewObject<ULowercaseVector2D>());
		newObject->x = x;
		newObject->y = y;
		return newObject;
	}

	FString ToString()
	{
		return FString::Printf(TEXT("X: %f | Y:%f"), this->x, this->y);
	}
};

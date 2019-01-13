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

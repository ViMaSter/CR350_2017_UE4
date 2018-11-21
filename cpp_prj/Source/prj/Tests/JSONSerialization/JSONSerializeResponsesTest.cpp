// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#include "WebSocketBlueprintLibrary.h"
#include "DataFormats/Response/SessionJoin.h"
#include "DataFormats/Response/SessionUpdate.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeResponsesSessionJoinTest, "Game.JSON.Responses.SessionJoin", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeResponsesSessionJoinTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString sessionJoinJSON(TEXT("{\"command\":\"sessionJoin\",\"sessionID\":2,\"session\":{\"playerPositionX\":-1.0,\"playerPositionY\":10.0,\"health\":20.0}}"));
	{
		USessionJoin* sessionJoinObject = Cast<USessionJoin>(UWebSocketBlueprintLibrary::JsonToObject(sessionJoinJSON, USessionJoin::StaticClass(), true));
		TestEqual<FString>(TEXT("Parsed sessionJoin 'command' should equal hand-crafted string"), sessionJoinObject->command, TEXT("sessionJoin"));
		TestEqual<int32>(TEXT("Parsed sessionJoin 'sessionID' should equal hand-crafted string"), sessionJoinObject->sessionID, 2);
		TestEqual<float>(TEXT("Parsed sessionJoin 'playerPositionX' should equal hand-crafted string"), sessionJoinObject->session->playerPositionX, -1.0f);
		TestEqual<float>(TEXT("Parsed sessionJoin 'playerPositionY' should equal hand-crafted string"), sessionJoinObject->session->playerPositionY, 10.0f);
		TestEqual<float>(TEXT("Parsed sessionJoin 'health' should equal hand-crafted string"), sessionJoinObject->session->health, 20.0f);
	}

	{
		USessionJoin* sessionJoinObject = Cast<USessionJoin>(UWebSocketBlueprintLibrary::JsonToObject(sessionJoinJSON, USessionJoin::StaticClass(), true));
		TestNotEqual<int32>(TEXT("Parsed sessionJoin 'sessionID' should equal hand-crafted string"), sessionJoinObject->sessionID, 3);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'playerPositionX' should equal hand-crafted string"), sessionJoinObject->session->playerPositionX, 0.0f);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'playerPositionY' should equal hand-crafted string"), sessionJoinObject->session->playerPositionY, 30.0f);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'health' should equal hand-crafted string"), sessionJoinObject->session->health, 40.0f);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeResponsesSessionUpdateTest, "Game.JSON.Responses.SessionUpdate", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeResponsesSessionUpdateTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString sessionJoinJSON(TEXT("{\"command\":\"sessionUpdate\",\"sessionID\":2,\"session\":{\"playerPositionX\":-1.0,\"playerPositionY\":10.0,\"health\":20.0}}"));
	{
		USessionUpdate* sessionJoinObject = Cast<USessionUpdate>(UWebSocketBlueprintLibrary::JsonToObject(sessionJoinJSON, USessionUpdate::StaticClass(), true));
		TestEqual<FString>(TEXT("Parsed sessionJoin 'command' should equal hand-crafted string"), sessionJoinObject->command, TEXT("sessionUpdate"));
		TestEqual<int32>(TEXT("Parsed sessionJoin 'sessionID' should equal hand-crafted string"), sessionJoinObject->sessionID, 2);
		TestEqual<float>(TEXT("Parsed sessionJoin 'playerPositionX' should equal hand-crafted string"), sessionJoinObject->session->playerPositionX, -1.0f);
		TestEqual<float>(TEXT("Parsed sessionJoin 'playerPositionY' should equal hand-crafted string"), sessionJoinObject->session->playerPositionY, 10.0f);
		TestEqual<float>(TEXT("Parsed sessionJoin 'health' should equal hand-crafted string"), sessionJoinObject->session->health, 20.0f);
	}

	{
		USessionUpdate* sessionJoinObject = Cast<USessionUpdate>(UWebSocketBlueprintLibrary::JsonToObject(sessionJoinJSON, USessionUpdate::StaticClass(), true));
		TestNotEqual<int32>(TEXT("Parsed sessionJoin 'sessionID' should equal hand-crafted string"), sessionJoinObject->sessionID, 3);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'playerPositionX' should equal hand-crafted string"), sessionJoinObject->session->playerPositionX, 0.0f);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'playerPositionY' should equal hand-crafted string"), sessionJoinObject->session->playerPositionY, 30.0f);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'health' should equal hand-crafted string"), sessionJoinObject->session->health, 40.0f);
	}

	return true;
}
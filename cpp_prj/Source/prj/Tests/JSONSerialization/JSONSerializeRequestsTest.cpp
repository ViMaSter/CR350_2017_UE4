// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#include "WebSocketBlueprintLibrary.h"
#include "DataFormats/Request/CreateSession.h"
#include "DataFormats/Request/UpdateSession.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeRequestsCreateSessionTest, "Game.JSON.Requests.CreateSession", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeRequestsCreateSessionTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString createSessionJSON(TEXT("{\"parameters\":{\"playerPositionX\":-1,\"playerPositionY\":10,\"health\":20},\"command\":\"createSession\"}"));
	UWebSocketBlueprintLibrary::ObjectToJson(UCreateSession::Create(USessionData::Create(-1.0f, 10.0f, 20.0f)), generatedString);
	TestEqual<FString>(TEXT("Hand crafted JSON string should equal generated string"), createSessionJSON, generatedString);
	UWebSocketBlueprintLibrary::ObjectToJson(UCreateSession::Create(USessionData::Create(0.0f, 30.0f, 40.0f)), generatedString);
	TestNotEqual<FString>(TEXT("Hand crafted JSON string should not equal generated string"), createSessionJSON, generatedString);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeRequestsUpdateSessionTest, "Game.JSON.Requests.UpdateSession", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeRequestsUpdateSessionTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString updateSessionJSON(TEXT("{\"sessionID\":-1,\"parameters\":{\"playerPositionX\":-1,\"playerPositionY\":10,\"health\":20},\"command\":\"updateSession\"}"));
	UWebSocketBlueprintLibrary::ObjectToJson(UUpdateSession::Create(-1, USessionData::Create(-1.0f, 10.0f, 20.0f)), generatedString);
	TestEqual<FString>(TEXT("Hand crafted JSON string should equal generated string"), updateSessionJSON, generatedString);
	UWebSocketBlueprintLibrary::ObjectToJson(UUpdateSession::Create(-1, USessionData::Create(0.0f, 30.0f, 40.0f)), generatedString);
	TestNotEqual<FString>(TEXT("Hand crafted JSON string should not equal generated string"), updateSessionJSON, generatedString);

	return true;
}
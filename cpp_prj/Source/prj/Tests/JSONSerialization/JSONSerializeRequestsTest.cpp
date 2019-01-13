// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#include "WebSocketBlueprintLibrary.h"
#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"
#include "DataFormats/Request/CreateSession.h"
#include "DataFormats/Request/UpdateSession.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeRequestsCreateSessionTest, "Game.JSON.Requests.CreateSession", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeRequestsCreateSessionTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	// command-parameter will be appended, due to member-ordering in C++ when deriving from other classes (UCreateSession derived from UCommand)
	// see: https://stackoverflow.com/a/2007980
	FString createSessionJSON(TEXT("{\"session\":{\"mapName\":\"Sand Castle\",\"timelimit\":180000,\"currentMatchStart\":12345},\"player\":{\"name\":\"UE4 Player\",\"position\":{\"x\":1,\"y\":2},\"colorHex\":4160243},\"command\":\"createSession\"}"));
	UWebSocketBlueprintLibrary::ObjectToJson(UCreateSession::Create(USessionData::Create("Sand Castle", 3 * 60 * 1000, 12345), UPlayerData::Create("UE4 Player", 1.0f, 2.0f, 0x3F7AF3)), generatedString);
	TestEqual<FString>(TEXT("Hand crafted JSON string should equal generated string"), createSessionJSON, generatedString);
	UWebSocketBlueprintLibrary::ObjectToJson(UCreateSession::Create(USessionData::Create("something_else", 2000, 54321), UPlayerData::Create("Not a UE4 Player", 0.0f, 0.0f, 0x00C0FF)), generatedString);
	TestNotEqual<FString>(TEXT("Hand crafted JSON string should not equal generated string"), createSessionJSON, generatedString);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeRequestsUpdateSessionTest, "Game.JSON.Requests.UpdateSession", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeRequestsUpdateSessionTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString updateSessionJSON(TEXT("{\"session\":{\"mapName\":\"Sand Castle\",\"timelimit\":180000,\"currentMatchStart\":12345},\"player\":{\"name\":\"UE4 Player\",\"position\":{\"x\":1,\"y\":2},\"colorHex\":4160243},\"command\":\"updateSession\"}"));
	UWebSocketBlueprintLibrary::ObjectToJson(UUpdateSession::Create(USessionData::Create("Sand Castle", 3 * 60 * 1000, 12345), UPlayerData::Create("UE4 Player", 1.0f, 2.0f, 0x3F7AF3)), generatedString);
	TestEqual<FString>(TEXT("Hand crafted JSON string should equal generated string"), updateSessionJSON, generatedString);
	UWebSocketBlueprintLibrary::ObjectToJson(UUpdateSession::Create(USessionData::Create("something_else", 2000, 54321), UPlayerData::Create("Not a UE4 Player", 0.0f, 0.0f, 0x00C0FF)), generatedString);
	TestNotEqual<FString>(TEXT("Hand crafted JSON string should not equal generated string"), updateSessionJSON, generatedString);

	return true;
}
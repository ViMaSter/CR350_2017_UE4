// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#include "WebSocketBlueprintLibrary.h"
#include "DataFormats/LowercaseVector2D.h"
#include "DataFormats/SessionData.h"
#include "DataFormats/PlayerData.h"
#include "DataFormats/Response/SessionJoin.h"
#include "DataFormats/Response/SessionUpdate.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeResponsesSessionJoinTest, "Game.JSON.Responses.SessionJoin", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeResponsesSessionJoinTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString sessionJoinJSON(TEXT("{\"session\":{\"mapName\":\"Sand Castle\",\"timelimit\":180000,\"currentMatchStart\":12345},\"player\":{\"name\":\"UE4 Player\",\"position\":{\"x\":1,\"y\":2},\"colorHex\":4160243},\"command\":\"sessionJoin\",\"sessionID\":\"17\"}"));
	{
		USessionJoin* sessionJoinObject = Cast<USessionJoin>(UWebSocketBlueprintLibrary::JsonToObject(sessionJoinJSON, USessionJoin::StaticClass(), true));
		TestEqual<FString>(TEXT("Parsed sessionJoin 'command' should equal hand-crafted string"), sessionJoinObject->command, TEXT("sessionJoin"));
		TestEqual<int32>(TEXT("Parsed sessionJoin 'command' should equal hand-crafted string"), sessionJoinObject->sessionID, 17);
		TestEqual<FString>(TEXT("Parsed sessionJoin 'mapName' should equal hand-crafted string"), sessionJoinObject->session->mapName, TEXT("Sand Castle"));
		TestEqual<int32>(TEXT("Parsed sessionJoin 'timelimit' should equal hand-crafted string"), sessionJoinObject->session->timelimit, 3 * 60 * 1000);
		TestEqual<int32>(TEXT("Parsed sessionJoin 'currentMatchStart' should equal hand-crafted string"), sessionJoinObject->session->currentMatchStart, 12345);
		TestEqual<FString>(TEXT("Parsed sessionJoin 'name' should equal hand-crafted string"), sessionJoinObject->player->name, TEXT("UE4 Player"));
		TestEqual<float>(TEXT("Parsed sessionJoin 'x' should equal hand-crafted string"), sessionJoinObject->player->position->GetX(), 1.0f);
		TestEqual<float>(TEXT("Parsed sessionJoin 'y' should equal hand-crafted string"), sessionJoinObject->player->position->GetY(), 2.0f);
		TestEqual<int32>(TEXT("Parsed sessionJoin 'colorHex' should equal hand-crafted string"), sessionJoinObject->player->colorHex, 0x3F7AF3);
	}

	{
		USessionJoin* sessionJoinObject = Cast<USessionJoin>(UWebSocketBlueprintLibrary::JsonToObject(sessionJoinJSON, USessionJoin::StaticClass(), true));
		TestNotEqual<FString>(TEXT("Parsed sessionJoin 'command' should not equal hand-crafted string"), sessionJoinObject->command, TEXT("sessionUpdate"));
		TestNotEqual<int32>(TEXT("Parsed sessionJoin 'command' should not equal hand-crafted string"), sessionJoinObject->sessionID, 0);
		TestNotEqual<FString>(TEXT("Parsed sessionJoin 'mapName' should not equal hand-crafted string"), sessionJoinObject->session->mapName, TEXT("something_else"));
		TestNotEqual<int32>(TEXT("Parsed sessionJoin 'timelimit' should not equal hand-crafted string"), sessionJoinObject->session->timelimit, 2000);
		TestNotEqual<int32>(TEXT("Parsed sessionJoin 'currentMatchStart' should not equal hand-crafted string"), sessionJoinObject->session->currentMatchStart, 54321);
		TestNotEqual<FString>(TEXT("Parsed sessionJoin 'name' should not equal hand-crafted string"), sessionJoinObject->player->name, TEXT("Not a UE4 Player"));
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'x' should not equal hand-crafted string"), sessionJoinObject->player->position->GetX(), 0.0f);
		TestNotEqual<float>(TEXT("Parsed sessionJoin 'y' should not equal hand-crafted string"), sessionJoinObject->player->position->GetY(), 0.0f);
		TestNotEqual<int32>(TEXT("Parsed sessionJoin 'colorHex' should not equal hand-crafted string"), sessionJoinObject->player->colorHex, 0x00C0FF);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJSONSerializeResponsesSessionUpdateTest, "Game.JSON.Responses.SessionUpdate", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FJSONSerializeResponsesSessionUpdateTest::RunTest(const FString& Parameters)
{
	FString generatedString;

	FString sessionUpdateJSON(TEXT("{\"session\":{\"mapName\":\"Sand Castle\",\"timelimit\":180000,\"currentMatchStart\":12345},\"player\":{\"name\":\"UE4 Player\",\"position\":{\"x\":1,\"y\":2},\"colorHex\":4160243},\"command\":\"sessionUpdate\"}"));
	{
		USessionUpdate* sessionUpdateObject = Cast<USessionUpdate>(UWebSocketBlueprintLibrary::JsonToObject(sessionUpdateJSON, USessionUpdate::StaticClass(), true));
		TestEqual<FString>(TEXT("Parsed sessionUpdate 'command' should equal hand-crafted string"), sessionUpdateObject->command, TEXT("sessionUpdate"));
		TestEqual<FString>(TEXT("Parsed sessionUpdate 'mapName' should equal hand-crafted string"), sessionUpdateObject->session->mapName, TEXT("Sand Castle"));
		TestEqual<int32>(TEXT("Parsed sessionUpdate 'timelimit' should equal hand-crafted string"), sessionUpdateObject->session->timelimit, 3 * 60 * 1000);
		TestEqual<int32>(TEXT("Parsed sessionUpdate 'currentMatchStart' should equal hand-crafted string"), sessionUpdateObject->session->currentMatchStart, 12345);
		TestEqual<FString>(TEXT("Parsed sessionUpdate 'name' should equal hand-crafted string"), sessionUpdateObject->player->name, TEXT("UE4 Player"));
		TestEqual<float>(TEXT("Parsed sessionUpdate 'x' should equal hand-crafted string"), sessionUpdateObject->player->position->GetX(), 1.0f);
		TestEqual<float>(TEXT("Parsed sessionUpdate 'y' should equal hand-crafted string"), sessionUpdateObject->player->position->GetY(), 2.0f);
		TestEqual<int32>(TEXT("Parsed sessionUpdate 'colorHex' should equal hand-crafted string"), sessionUpdateObject->player->colorHex, 0x3F7AF3);
	}

	{
		USessionUpdate* sessionUpdateObject = Cast<USessionUpdate>(UWebSocketBlueprintLibrary::JsonToObject(sessionUpdateJSON, USessionUpdate::StaticClass(), true));
		TestNotEqual<FString>(TEXT("Parsed sessionUpdate 'command' should not equal hand-crafted string"), sessionUpdateObject->command, TEXT("sessionJoin"));
		TestNotEqual<FString>(TEXT("Parsed sessionUpdate 'mapName' should not equal hand-crafted string"), sessionUpdateObject->session->mapName, TEXT("something_else"));
		TestNotEqual<int32>(TEXT("Parsed sessionUpdate 'timelimit' should not equal hand-crafted string"), sessionUpdateObject->session->timelimit, 2000);
		TestNotEqual<int32>(TEXT("Parsed sessionUpdate 'currentMatchStart' should not equal hand-crafted string"), sessionUpdateObject->session->currentMatchStart, 54321);
		TestNotEqual<FString>(TEXT("Parsed sessionUpdate 'name' should not equal hand-crafted string"), sessionUpdateObject->player->name, TEXT("Not a UE4 Player"));
		TestNotEqual<float>(TEXT("Parsed sessionUpdate 'x' should not equal hand-crafted string"), sessionUpdateObject->player->position->GetX(), 0.0f);
		TestNotEqual<float>(TEXT("Parsed sessionUpdate 'y' should not equal hand-crafted string"), sessionUpdateObject->player->position->GetY(), 0.0f);
		TestNotEqual<int32>(TEXT("Parsed sessionUpdate 'colorHex' should not equal hand-crafted string"), sessionUpdateObject->player->colorHex, 0x00C0FF);
	}

	return true;

	return true;
}
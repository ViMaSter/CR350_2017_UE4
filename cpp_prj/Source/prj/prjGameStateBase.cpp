// Fill out your copyright notice in the Description page of Project Settings.

#include "prjGameStateBase.h"

template<typename T>
static FString EnumToString(const FString& enumName, const T value)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
	return *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "null");
}

void AprjGameStateBase::SetConnectionStatus(EConnectionStatus newStatus)
{
	OnConnectionStatusChanged.Broadcast(connectionStatus, newStatus);

	UE_LOG(LogWindows, Warning,
		TEXT("Connection status changed from '%s' to '%s'"),
		*EnumToString("EConnectionStatus", connectionStatus),
		*EnumToString("EConnectionStatus", newStatus)
	);

	connectionStatus = newStatus;
}

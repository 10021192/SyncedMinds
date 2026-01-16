// Copyright Epic Games, Inc. All Rights Reserved.

#include "SyncedMindsGameMode.h"

ASyncedMindsGameMode::ASyncedMindsGameMode()
{
	// stub
}

void ASyncedMindsGameMode::HostGame()
{
	GetWorld()->ServerTravel(TEXT("/Game/ThirdPerson/Lvl_ThirdPerson?listen"));
}

void ASyncedMindsGameMode::JoinGame()
{
	APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
	if (PC)
	{
		PC->ClientTravel(TEXT("192.168.1.64"), TRAVEL_Absolute);
	}
}
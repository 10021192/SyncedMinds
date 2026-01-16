// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SyncedMindsGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(MinimalAPI)
class ASyncedMindsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ASyncedMindsGameMode();
	
	UFUNCTION(BlueprintCallable)
		void HostGame();
	
	UFUNCTION(BlueprintCallable)
		void JoinGame();
};




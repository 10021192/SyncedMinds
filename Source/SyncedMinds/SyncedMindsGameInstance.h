// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SyncedMindsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SYNCEDMINDS_API USyncedMindsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="SyncedMinds|Network")
	void HostGame();

	UFUNCTION(BlueprintCallable, Category="SyncedMinds|Network")
	void JoinGame(const FString& Address);
	
	//Connect to matchmaking and join
	UFUNCTION(BlueprintCallable, Category="SyncedMinds|Network")
	void JoinViaMatchmaking();
	
private:
	// Matchmaking server configuration
	FString MatchmakingServerIP = TEXT("127.0.0.1");
	int32 MatchmakingServerPort = 5555;

	// Helper function to request server address from matchmaking
	FString RequestServerAddress();
};

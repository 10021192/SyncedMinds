#include "SyncedMindsGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void USyncedMindsGameInstance::HostGame()
{
	UGameplayStatics::OpenLevel(
		this,
		FName(TEXT("/Game/ThirdPerson/Lvl_ThirdPerson")),
		true,
		TEXT("listen")
	);
}

void USyncedMindsGameInstance::JoinGame(const FString& Address)
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;

	PC->ClientTravel(Address, TRAVEL_Absolute);
}
#include "SyncedMindsGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

void USyncedMindsGameInstance::HostGame()
{
	UGameplayStatics::OpenLevel(
		this,
		FName(TEXT("/Game/The_Lost_Ruins/Levels/The_Lost_Ruins")),
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

void USyncedMindsGameInstance::JoinViaMatchmaking()
{
	UE_LOG(LogTemp, Display, TEXT("Connecting to matchmaking server..."));
	
	FString ServerAddress = RequestServerAddress();
	
	if (ServerAddress.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get server address from matchmaking"));
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Received server address: %s"), *ServerAddress);
	JoinGame(ServerAddress);
}

FString USyncedMindsGameInstance::RequestServerAddress()
{
	// Get socket subsystem
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (!SocketSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get socket subsystem"));
		return FString();
	}

	// Create TCP socket
	FSocket* Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("MatchmakingSocket"), false);
	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
		return FString();
	}

	// Create matchmaking server address
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	bool bIsValid;
	Addr->SetIp(*MatchmakingServerIP, bIsValid);
	Addr->SetPort(MatchmakingServerPort);

	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid matchmaking server IP"));
		Socket->Close();
		SocketSubsystem->DestroySocket(Socket);
		return FString();
	}

	// Connect to matchmaking server
	if (!Socket->Connect(*Addr))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to matchmaking server at %s:%d"), *MatchmakingServerIP, MatchmakingServerPort);
		Socket->Close();
		SocketSubsystem->DestroySocket(Socket);
		return FString();
	}
	
	// Send protocol request 'g' (get server address)
	FString Request = TEXT("g");
	int32 BytesSent = 0;
	FTCHARToUTF8 Converter(*Request);
	Socket->Send((const uint8*)Converter.Get(), Converter.Length(), BytesSent);

	UE_LOG(LogTemp, Display, TEXT("Connected to matchmaking server"));

	// Wait briefly for data
	FPlatformProcess::Sleep(0.1f);

	// Receive server address
	uint8 Buffer[256];
	int32 BytesRead = 0;

	if (Socket->Recv(Buffer, sizeof(Buffer) - 1, BytesRead))
	{
		Buffer[BytesRead] = '\0';
		FString ServerAddress = UTF8_TO_TCHAR(Buffer);
		
		Socket->Close();
		SocketSubsystem->DestroySocket(Socket);
		return ServerAddress;
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to receive data from matchmaking server"));
	Socket->Close();
	SocketSubsystem->DestroySocket(Socket);
	return FString();
}
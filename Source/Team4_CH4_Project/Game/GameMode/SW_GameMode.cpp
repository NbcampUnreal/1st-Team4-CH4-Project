#include "Team4_CH4_Project/Game/GameMode/SW_GameMode.h"
#include "Team4_CH4_Project/Game/GameState/SW_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

ASW_GameMode::ASW_GameMode()
{
	PostLoginActivate = false;
}

void ASW_GameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GameMode Swapped"));
	if (!PostLoginActivate)
	{
		ServerPlayerControllers.Empty();
	
		TArray<AActor*> FoundPlayerControllers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), FoundPlayerControllers);
		
		for (AActor* PlayerControllerActor : FoundPlayerControllers)
		{
			APlayerController* PlayerController = Cast<APlayerController>(PlayerControllerActor);
			if (PlayerController && !ServerPlayerControllers.Contains(PlayerController))
			{
				ServerPlayerControllers.Add(PlayerController);
				UE_LOG(LogTemp, Warning, TEXT("Added PlayerController (using GetAllActorsOfClass) to ServerPlayerControllers: %s"), *PlayerController->GetName());
			}
		}
	}
}


void ASW_GameMode::HandleGameEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleGameEnd Entrance"));
	FTimerHandle GameEndTimerHandle;
	GetWorldTimerManager().SetTimer(GameEndTimerHandle, this, &ASW_GameMode::DelayedTravelToLobby, 5.0f, false);
}

void ASW_GameMode::DelayedTravelToLobby()
{
	if (HasAuthority() && !LobbyMapName.IsEmpty())
	{
		// 서버 트래블 시작
		CreateSession();
		GetWorld()->ServerTravel(LobbyMapName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to travel to lobby: Not a server or LobbyMapName is empty."));
	}
}

TArray<APlayerController*> ASW_GameMode::GetServerPlayerControllers()
{
	return ServerPlayerControllers;
}


void ASW_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Activate"));
	ServerPlayerControllers.Add(NewPlayer);
	PostLoginActivate = true;
	if (AGameStateBase* GS = GetWorld()->GetGameState())
	{
		if (ASW_GameState* SWGS = Cast<ASW_GameState>(GS))
		{
			SWGS->SetCurrentPlayerAmount(1);
			SWGS->AddPlayerStates(NewPlayer);
		}
	}
}

void ASW_GameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}


void ASW_GameMode::Multicast_EndGame_Implementation()
{
	PopUpResult();
	UE_LOG(LogTemp, Warning, TEXT("Round Is Over"));
	HandleGameEnd();
}

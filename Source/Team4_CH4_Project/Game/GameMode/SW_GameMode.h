#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SW_GameMode.generated.h"


class USW_TestCharacterClassInfo;


UCLASS()
class TEAM4_CH4_PROJECT_API ASW_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASW_GameMode();
	virtual void BeginPlay() override;
	
	void HandleGameEnd();
	
	void DelayedTravelToLobby();

	UFUNCTION(BlueprintImplementableEvent)
	void PopUpResult();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateSession();
	
	UFUNCTION()
	TArray<APlayerController*> GetPlayerControllers();
	
	UPROPERTY(EditDefaultsOnly, Category = "GameEndLevel")
	FString LobbyMapName;
protected:
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_EndGame();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<APlayerController*> PlayerControllers;
};

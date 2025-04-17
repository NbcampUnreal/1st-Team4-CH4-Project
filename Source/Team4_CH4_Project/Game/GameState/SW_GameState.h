#pragma once

#include "CoreMinimal.h"
#include "SW_PlayerController.h"
#include "GameFramework/GameState.h"
#include "SW_GameState.generated.h"

class ASW_PlayerState;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_GameState : public AGameState
{
	GENERATED_BODY()

public:
	ASW_GameState();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void SetCurrentPlayerAmount(int AddAmount);

	UFUNCTION(BlueprintCallable)
	float GetRoundTimeLeft();

	UFUNCTION()
	void ShowDebug() const;

	UFUNCTION()
	void OnRep_DoEndGame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintAuthorityOnly)
	void AddRanking(APlayerController* DeadUserPC);

	UFUNCTION()
	void AddPlayerStates(APlayerController* const NewPlayerPC);
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="RoundSettings")
	float RoundDuration;

protected:
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category="RoundSettings")
	float RoundTimeLeft;
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category="CurrentGame")
	int CurrentPlayerAmount;

	UPROPERTY(Replicated, BlueprintReadWrite, Category="CurrentGame")
	bool bPlayerIn;

	UPROPERTY(BlueprintReadWrite, Category="CurrentGame")
	bool bGameEnd;

	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerState*> PlayerStatesForRank;
	
	TArray<ASW_PlayerState*> PlayerStates;
private:
};

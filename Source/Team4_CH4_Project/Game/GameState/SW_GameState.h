#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SW_GameState.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_GameState : public AGameState
{
	GENERATED_BODY()

public:
	ASW_GameState();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	

	// 라운드가 종료되었는지 여부
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool bIsRoundOver;

	// 현재 생존한 플레이어 수
	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 RemainingPlayers;

	// 승리한 플레이어 이름 (한 명 남았을 경우)
	UPROPERTY(BlueprintReadOnly, Replicated)
	FString WinningPlayerName;

	// 라운드 총 지속 시간 (초)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RoundDuration;

	void SetRoundTime(float SetCurrentRoundTime);
protected:
	UPROPERTY(BlueprintReadOnly, Replicated)
	float RoundTime;

	FTimerHandle RoundTimerHandle;
	FTimerHandle CheckStateTimerHandle;

	void UpdateRoundTime();
	void CheckGameState();
	UFUNCTION()
	void EndGame() const;
};
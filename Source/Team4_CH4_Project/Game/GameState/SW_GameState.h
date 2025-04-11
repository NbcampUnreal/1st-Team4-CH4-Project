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
};

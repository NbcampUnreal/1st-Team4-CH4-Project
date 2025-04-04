#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Brall.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Brall : public ASW_CharacterBase
{
	GENERATED_BODY()

public:
	ASW_Brall();

public:

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;
};

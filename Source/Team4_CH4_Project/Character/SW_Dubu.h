#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Dubu.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Dubu : public ASW_CharacterBase
{
	GENERATED_BODY()
	
public:
	ASW_Dubu();

public:

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Player_Move(const FInputActionValue& _InputValue) override;

	UFUNCTION(BlueprintCallable)
	virtual void Player_Jump(const FInputActionValue& _InputValue) override;

};

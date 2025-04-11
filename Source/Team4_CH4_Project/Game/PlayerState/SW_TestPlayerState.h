#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "SW_TestPlayerState.generated.h"


class USW_TestAbilitySystemComponent;
class USW_TestAttributeSet;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_TestPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ASW_TestPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	USW_TestAbilitySystemComponent* GetSW_AbilitySystemComponent() const;

	UFUNCTION(BlueprintPure)
	USW_TestAttributeSet* GetSW_Attributes() const;


private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USW_TestAbilitySystemComponent> SW_AbilitySystemComp;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USW_TestAttributeSet> SW_Attributes;
};

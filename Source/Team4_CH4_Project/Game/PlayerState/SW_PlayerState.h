#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "SW_PlayerState.generated.h"


class USW_AbilitySystemComponent;
class USW_AttributeSet;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ASW_PlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	USW_AbilitySystemComponent* GetSW_AbilitySystemComponent() const;

	UFUNCTION(BlueprintPure)
	USW_AttributeSet* GetSW_Attributes() const;


private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USW_AbilitySystemComponent> SW_AbilitySystemComp;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<USW_AttributeSet> SW_Attributes;
};

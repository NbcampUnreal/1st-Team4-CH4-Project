#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SW_AbilitySystemComponent.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveToGrant);
	void InitializeDefaultAttribute(const TSubclassOf<UGameplayEffect> AttributeEffect);
	
};

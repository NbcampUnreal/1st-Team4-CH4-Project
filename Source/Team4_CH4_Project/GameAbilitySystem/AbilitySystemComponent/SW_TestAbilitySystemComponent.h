#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SW_TestAbilitySystemComponent.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USW_TestAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveToGrant);
	void InitializeDefaultAttribute(const TSubclassOf<UGameplayEffect> AttributeEffect);
	
};

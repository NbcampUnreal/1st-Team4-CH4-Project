#include "Team4_CH4_Project/GameAbilitySystem/AbilitySystemComponent/SW_TestAbilitySystemComponent.h"

void USW_TestAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f);
		GiveAbility(AbilitySpec);
	}
}

void USW_TestAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& PassiveToGrant)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : PassiveToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void USW_TestAbilitySystemComponent::InitializeDefaultAttribute(const TSubclassOf<UGameplayEffect> AttributeEffect)
{
	checkf(AttributeEffect, TEXT("No valid default attribute for this Character %s"), *GetAvatarActor()->GetName());
	const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(AttributeEffect, 1.f, ContextHandle);
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

#include "Team4_CH4_Project/Game/PlayerState/SW_TestPlayerState.h"
#include "Team4_CH4_Project/GameAbilitySystem/AbilitySystemComponent/SW_TestAbilitySystemComponent.h"
#include "Team4_CH4_Project/GameAbilitySystem/Attributes/SW_TestAttributeSet.h"

ASW_TestPlayerState::ASW_TestPlayerState()
{
	NetUpdateFrequency = 100.f;
	MinNetUpdateFrequency = 66.f;

	SW_AbilitySystemComp = CreateDefaultSubobject<USW_TestAbilitySystemComponent>("AbilitySystemComp");
	SW_AbilitySystemComp->SetIsReplicated(true);
	SW_AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	SW_Attributes = CreateDefaultSubobject<USW_TestAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASW_TestPlayerState::GetAbilitySystemComponent() const
{
	return SW_AbilitySystemComp;
}

USW_TestAbilitySystemComponent* ASW_TestPlayerState::GetSW_AbilitySystemComponent() const
{
	return SW_AbilitySystemComp;
}

USW_TestAttributeSet* ASW_TestPlayerState::GetSW_Attributes() const
{
	return SW_Attributes;
}

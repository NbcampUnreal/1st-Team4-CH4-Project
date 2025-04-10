#include "Team4_CH4_Project/Game/PlayerState/SW_PlayerState.h"
#include "Team4_CH4_Project/GameAbilitySystem/AbilitySystemComponent/SW_AbilitySystemComponent.h"
#include "Team4_CH4_Project/GameAbilitySystem/Attributes/SW_AttributeSet.h"

ASW_PlayerState::ASW_PlayerState()
{
	NetUpdateFrequency = 100.f;
	MinNetUpdateFrequency = 66.f;

	SW_AbilitySystemComp = CreateDefaultSubobject<USW_AbilitySystemComponent>("AbilitySystemComp");
	SW_AbilitySystemComp->SetIsReplicated(true);
	SW_AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	SW_Attributes = CreateDefaultSubobject<USW_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASW_PlayerState::GetAbilitySystemComponent() const
{
	return SW_AbilitySystemComp;
}

USW_AbilitySystemComponent* ASW_PlayerState::GetSW_AbilitySystemComponent() const
{
	return SW_AbilitySystemComp;
}

USW_AttributeSet* ASW_PlayerState::GetSW_Attributes() const
{
	return SW_Attributes;
}

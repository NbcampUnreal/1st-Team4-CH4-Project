#include "Team4_CH4_Project/GameAbilitySystem/Libraries/SW_AbilitySystemLibrary.h"
#include "Team4_CH4_Project/Game/GameMode/SW_GameMode.h"
#include "Kismet/GameplayStatics.h"

USW_CharacterClassInfo* USW_AbilitySystemLibrary::GetCharacterClassDefaultInfo(const UObject* WorldContextObject)
{
	if (const ASW_GameMode* SWGamemode = Cast<ASW_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return SWGamemode->GetCharacterClassDefaultInfo();
	}

	return nullptr;
}

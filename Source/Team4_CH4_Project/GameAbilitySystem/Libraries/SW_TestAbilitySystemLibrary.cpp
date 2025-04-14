#include "Team4_CH4_Project/GameAbilitySystem/Libraries/SW_TestAbilitySystemLibrary.h"
#include "Team4_CH4_Project/Game/GameMode/SW_GameMode.h"
#include "Kismet/GameplayStatics.h"

USW_TestCharacterClassInfo* USW_TestAbilitySystemLibrary::GetCharacterClassDefaultInfo(const UObject* WorldContextObject)
{
	if (const ASW_GameMode* SWGamemode = Cast<ASW_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
	}

	return nullptr;
}

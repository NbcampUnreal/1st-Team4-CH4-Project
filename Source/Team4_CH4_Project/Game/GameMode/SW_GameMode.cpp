#include "Team4_CH4_Project/Game/GameMode/SW_GameMode.h"

USW_CharacterClassInfo* ASW_GameMode:: GetCharacterClassDefaultInfo() const
{
	return ClassDefaults;
}

void ASW_GameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	int Controllers = GetWorld()->GetNumPlayerControllers();
	UE_LOG(LogTemp, Warning, TEXT("The PlayerController value is: %d"), Controllers);
}


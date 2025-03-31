// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team4_CH4_ProjectGameMode.h"
#include "Team4_CH4_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeam4_CH4_ProjectGameMode::ATeam4_CH4_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

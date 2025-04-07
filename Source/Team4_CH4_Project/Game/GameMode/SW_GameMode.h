#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SW_GameMode.generated.h"

class USW_CharacterClassInfo;


UCLASS()
class TEAM4_CH4_PROJECT_API ASW_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	USW_CharacterClassInfo* GetCharacterClassDefaultInfo() const;
private:

	UPROPERTY(EditDefaultsOnly, Category= "Custom Values|Class Defaults")
	TObjectPtr<USW_CharacterClassInfo> ClassDefaults;
};

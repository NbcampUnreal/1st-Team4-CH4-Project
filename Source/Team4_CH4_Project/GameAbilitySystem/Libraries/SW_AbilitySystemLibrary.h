#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SW_AbilitySystemLibrary.generated.h"

class USW_CharacterClassInfo;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_AbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BLueprintPure)
	static USW_CharacterClassInfo* GetCharacterClassDefaultInfo(const UObject* WorldContextObject);
};

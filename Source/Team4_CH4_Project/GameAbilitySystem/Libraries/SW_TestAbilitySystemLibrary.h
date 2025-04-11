#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SW_TestAbilitySystemLibrary.generated.h"

class USW_TestCharacterClassInfo;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_TestAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BLueprintPure)
	static USW_TestCharacterClassInfo* GetCharacterClassDefaultInfo(const UObject* WorldContextObject);
};

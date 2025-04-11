
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SW_CharacterClassInfo.generated.h"


class UGameplayEffect;
class UGameplayAbility;


USTRUCT()
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttribute;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingPassive;
};

UCLASS()
class TEAM4_CH4_PROJECT_API USW_CharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FCharacterClassDefaultInfo> ClassDefaultInfoMap;
};

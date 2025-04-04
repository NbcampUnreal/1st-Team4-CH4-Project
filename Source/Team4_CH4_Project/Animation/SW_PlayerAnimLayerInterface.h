#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SW_PlayerAnimLayerInterface.generated.h"

UINTERFACE(BlueprintType)
class USW_PlayerAnimLayerInterface : public UInterface
{
	GENERATED_BODY()
};

class TEAM4_CH4_PROJECT_API ISW_PlayerAnimLayerInterface
{
	GENERATED_BODY()

public:

	// 점프공격
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayJumpAttack();

	// 대쉬공격
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayDashSkill();

	//기본스킬공격
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayNormalSkill();

	//궁극기스킬공격
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlaySpecialSkill();
};

#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Arrow.h"
#include "SW_MythSpawnActor.h"
#include "Components/BoxComponent.h"
#include "SW_Myth.generated.h"

struct TFimerhandle;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Myth : public ASW_CharacterBase
{
	GENERATED_BODY()

public:
	ASW_Myth();

	virtual void ComboAttack() override;

	AActor* SpawnArrow(bool bFanShape, bool bIsNormalSkill = false);

	virtual void BeginPlay() override;

	virtual void NormalSkill() override;

	virtual void DashSkill() override;

	virtual void JumpAttack() override;

	virtual void SpecialSkill() override;

	void SpawnComboArrow(bool bIsSpecialSkill = false);

	// 궁수 전용 투사체 클래스 (화살)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Myth")
	TSubclassOf<ASW_Arrow> ArrowProjectileClass;

	// 점프 어택시 스폰할 액터를 넣을 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Myth")
	TSubclassOf<AActor> MythSpawnActorClass;

	FTimerHandle JumpAttackFlagTimerHandle;

	bool bIsJumpAttacking;


	// 화살 머테리얼들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow Materials")
	UMaterialInterface* FirstMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow Materials")
	UMaterialInterface* SecondMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow Materials")
	UMaterialInterface* ThirdMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow Materials")
	UMaterialInterface* NormalSkillMaterial;

	FTimerHandle DashTimerHandle;
};

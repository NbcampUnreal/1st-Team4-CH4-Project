#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Myth.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Myth : public ASW_CharacterBase
{
	GENERATED_BODY()

public:
	ASW_Myth();

	UFUNCTION(BlueprintCallable, Category = "Myth")
	virtual void ComboAttack() override;
	AActor* SpawnArrow();

	virtual void NormalSkill() override;

	UFUNCTION(BlueprintCallable, Category = "Myth")
	void DashAttack();
	void ExecuteDash();
	void SpawnComboArrow();

	UFUNCTION(BlueprintCallable, Category = "Myth")
	void UltimateSkill();

	UFUNCTION(BlueprintCallable, Category = "Myth")
	void DownAttack();

	// 궁수 전용 투사체 클래스 (화살)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Myth")
	TSubclassOf<AActor> ArrowProjectileClass;

	// 궁극 사용 시 무적 상태 플래그
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Myth")
	bool bIsInvincible;

	// 화살 머테리얼들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrow Materials")
	UMaterialInterface* FirstMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrow Materials")
	UMaterialInterface* SecondMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrow Materials")
	UMaterialInterface* ThirdMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrow Materials")
	UMaterialInterface* NormalSkillMaterial;
	
    FTimerHandle DashTimerHandle;


protected:
	virtual void BeginPlay() override;
};

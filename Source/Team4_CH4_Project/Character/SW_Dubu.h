#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Dubu.generated.h"

class UBoxComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Dubu : public ASW_CharacterBase
{
	GENERATED_BODY()

public:
	ASW_Dubu();

	virtual void BeginPlay() override;
	virtual void DashSkill() override;
	virtual void JumpAttack() override;

public:
	
	// 대쉬 데미지용 박스 콜리전
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UBoxComponent* DashCollider;
	// ============================================

	// 궁극기용 던지는 액터 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    TSubclassOf<AActor> ThrowActorClass;

	// 대쉬 스킬용 몸 전체 콜리전 데미지 함수
	UFUNCTION()
	void OnDashBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


public:

	// 궁극기 스킬용 함수
	UFUNCTION()
	void ThrowUltimateSkill();
};

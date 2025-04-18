#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_SkillEffectActor.h"
#include "SW_Brall.generated.h"

class UBoxComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Brall : public ASW_CharacterBase
{
    GENERATED_BODY()

public:
    ASW_Brall();

public:
    virtual void BeginPlay() override;
    virtual void DashSkill() override;
    virtual void JumpAttack() override;
    // 점프어택 착지시 나이아가라 이펙트용
    virtual void Landed(const FHitResult& Hit) override;


public:
    FTimerHandle DashTimerHandle;


protected:

    // 칼 액터 컴포넌트 (BP에서 ChildActor로 붙임)
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    UChildActorComponent* Sword;

    // 대쉬용 캐릭터 몸 콜리전
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    UBoxComponent* DashCollider; // ✅ 대시 데미지용 박스 콜리전 추가

    // 점프어택 이펙트 블루프린트 클래스 지정용
    UPROPERTY(EditAnywhere, Category = "Effect")
    TSubclassOf<ASkillEffectActor> JumpLandEffectClass;

    // 대쉬 스킬용 몸 전체 콜리전 데미지 함수
    UFUNCTION()
    void OnDashBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult); // ✅ 대시용 오버랩 함수

public:

    // 대쉬스킬
    void ExecuteDesh();
};

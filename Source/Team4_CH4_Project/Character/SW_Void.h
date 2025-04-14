// SW_Void.h
#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Void.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Void : public ASW_CharacterBase
{
	GENERATED_BODY()

public:
	ASW_Void();

	// 기본 공격: 투사체 3콤보 (3번째 투사체는 2배 크기로 생성)
	virtual void ComboAttack() override;

	// 일반 스킬: 기본 공격과 유사하게 투사체 발사
	virtual void NormalSkill() override;

	virtual void JumpAttack() override;

	// 이동 스킬: 투사체와 위치 교환 혹은 전방 텔레포트
	virtual void DashSkill() override;

	// 궁극기: 텔레포트 및 추가 효과 연계 궁극기
	UFUNCTION(BlueprintCallable, Category = "Void")
	void UltimateSkill();

	// 마법사의 투사체 클래스 (SW_Magic 기반)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Void")
	TSubclassOf<AActor> SpellProjectileClass;

protected:
	// BeginPlay()를 오버라이드하는 경우 반복적으로 호출할 수 있도록 헤더에 선언합니다.
	virtual void BeginPlay() override;
};

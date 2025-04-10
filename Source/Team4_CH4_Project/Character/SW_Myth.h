// SW_Myth.h
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

	// 기본 평타 콤보 공격
	UFUNCTION(BlueprintCallable, Category = "Myth")
	void BasicAttack();

	// 일반 스킬: 애쉬 W 스타일, 부채꼴 화살 3발 발사
	virtual void NormalSkill() override;

	// 대시 공격: 전방 화살 발사와 동시에 전방 대시 후 후방 회피(백덤블링)
	UFUNCTION(BlueprintCallable, Category = "Myth")
	void DashAttack();

	// 궁극기: 무적 상태로 진입 후 좁은 범위로 화살 3발 발사
	UFUNCTION(BlueprintCallable, Category = "Myth")
	void UltimateSkill();

	// 다운 어택: 공격 없이 뒤로 백덤블링하며 이동 (보는 방향의 반대)
	UFUNCTION(BlueprintCallable, Category = "Myth")
	void DownAttack();

	// 궁수 전용 투사체 클래스 (화살)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Myth")
	TSubclassOf<AActor> ArrowProjectileClass;

	// 궁극 사용 시 무적 상태 플래그
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Myth")
	bool bIsInvincible;

protected:
	// BeginPlay()를 오버라이드하는 경우, 헤더에 선언해줘야 합니다.
	virtual void BeginPlay() override;
};

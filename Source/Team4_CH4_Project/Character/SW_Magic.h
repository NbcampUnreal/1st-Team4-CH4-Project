// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SW_ThrowActor.h"
#include "SW_Magic.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Magic : public ASW_ThrowActor
{
	GENERATED_BODY()

public:
	ASW_Magic();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// 마법 투사체의 충돌 처리: 다른 캐릭터에 닿아도 사라지지 않도록 부모 기능을 재정의함.
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult) override;

	/* =====================================================
	   마법 투사체 특화 변수들
	===================================================== */

	// 텔레포트(위치 교환) 활성화 여부.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magic")
	bool bTeleported;

	// 궁극 효과(위로 떠올랐다가 내려꽂히며 폭발) 실행 여부.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magic")
	bool bUltimateTriggered;

	// 텔레포트 후, 투사체가 해당 위치에 머무르는 지속 시간(초).
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magic")
	float TeleportLifeDuration;

	/* =====================================================
	   함수들
	===================================================== */

	// 마법사가 투사체와 위치를 바꾸는 순간 호출되는 함수.
	UFUNCTION(BlueprintCallable, Category = "Magic")
	void OnTeleportActivated();

	// 궁극기 시 투사체에 궁극 효과(위로 떠올랐다 내려꽂히며 폭발)를 실행하는 함수.
	UFUNCTION(BlueprintCallable, Category = "Magic")
	void TriggerUltimate();

private:
	// 텔레포트 활성 후 소멸을 위한 타이머 핸들.
	FTimerHandle TeleportLifeTimerHandle;

	// 궁극 효과 낙하 및 폭발 처리 함수.
	void OnUltimateImpact();

	// 타이머에 의해 호출되어 스스로 파괴하는 헬퍼 함수.
	void DestroySelf();
};

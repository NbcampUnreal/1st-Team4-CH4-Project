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

public:
	
	// 대쉬 데미지용 박스 콜리전
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UBoxComponent* DashCollider;


	// 손 충돌 처리용 =============================

	// 오른손
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UBoxComponent* RightHandCollider;
	// 왼손
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UBoxComponent* LeftHandCollider;
	// 콤보 중 중복 타격 방지용
	UPROPERTY()
	TSet<AActor*> AlreadyHitActors;
	// ============================================

	// 스페셜 스킬용 던지는 땅 스폰용 변수
	UPROPERTY(EditAnywhere, Category = "Skill")
	TSubclassOf<class ASW_ThrowActor> ThrowActorClass;



	// 콤보 평타용 오른손 콜리전 데미지 함수
	UFUNCTION()
	void OnRightHandOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
	// 콤보 평타용 왼손 콜리전 데미지 함수
	UFUNCTION()
	void OnLeftHandOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	// 대쉬 스킬용 몸 전체 콜리전 데미지 함수
	UFUNCTION()
	void OnDashBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


public:
	// 평타 노티파이용
	void RightHandStart();
	void RightHandEnd();
	void LeftHandStart();
	void LeftHandEnd();
};

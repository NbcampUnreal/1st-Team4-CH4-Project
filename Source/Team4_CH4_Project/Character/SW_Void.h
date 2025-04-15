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

protected:
	// BeginPlay()를 오버라이드하는 경우 반복적으로 호출할 수 있도록 헤더에 선언합니다.
	virtual void BeginPlay() override;

	// 기본 공격: 투사체 3콤보 (3번째 투사체는 1.5배 크기로 생성)
	virtual void ComboAttack() override;

	// 일반 스킬: 기본 공격과 유사하게 투사체 발사
	virtual void NormalSkill() override;

	virtual void JumpAttack() override;

	virtual void DashSkill() override;

	virtual void SpecialSkill() override;

public:

	// 공격스킬마다 다른 메시/머티리얼/나이아가라 생성용 ========================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void|Visual")
	UMaterialInterface* ComboMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void|Visual")
	UNiagaraSystem* ComboEffect;

	// 노멀 스킬용 메시 / 머티리얼 / 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void|Visual")
	UStaticMesh* NormalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void|Visual")
	UMaterialInterface* NormalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void|Visual")
	UNiagaraSystem* NormalEffect;
	// =====================================================================


	// Magic발사용 함수
	void SpawnComboMagic(); // 콤보에서 호출할 발사 함수

	// Normal스킬용 magic발사 함수
	UFUNCTION(BlueprintCallable, Category = "Void")
	void SpawnNormalMagic();


	// 노티파이에서 호출할 실제 텔레포트 함수
	UFUNCTION(BlueprintCallable, Category = "Void")
	void ExecuteDashTeleport();


	// 발사할 투사체 액터를 담을 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Void")
	TSubclassOf<AActor> SpellProjectileClass;

	// 궁극기에서 생성할 액터 담을 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Void|Ultimate")
	TSubclassOf<class ASW_VoidSpawnActor> VoidUltimateActorClass;
};

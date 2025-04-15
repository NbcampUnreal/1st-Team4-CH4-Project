#pragma once

#include "CoreMinimal.h"
#include "SW_ThrowActor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "SW_Magic.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Magic : public ASW_ThrowActor
{
	GENERATED_BODY()

public:
	ASW_Magic();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	int32 CurrentComboIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Mesh")
	UStaticMesh* NormalStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Material")
	UMaterialInterface* Combo1_M;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Material")
	UMaterialInterface* Combo2_M;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Material")
	UMaterialInterface* Combo3_M;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Material")
	UMaterialInterface* NormalSkillMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Effect")
	UNiagaraSystem* ComboEffectNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Effect")
	UNiagaraSystem* NormalSkillNiagara;



	// 나이아가라 이펙트 생성 함수
	void SpawnNiagaraEffect(UNiagaraSystem* NiagaraSystem);


	// 콤보어택 발사 메시크기설정용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Scale")
	FVector ComboScale = FVector(2.0f); 

	// 노멀스킬 발사 메시크기설정용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Scale")
	FVector NormalSkillScale = FVector(2.0f);

	// 머티/FX 적용용 함수
	UFUNCTION(BlueprintCallable, Category = "Magic")
	void ApplyVisualSettings(); 
};

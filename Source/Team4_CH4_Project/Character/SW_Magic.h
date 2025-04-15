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
    void SpawnNiagaraEffect(UNiagaraSystem* NiagaraSystem);

    // 콤보용 메시 스케일 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Scale")
    FVector ComboScale = FVector(2.5f);

    // 노멀스킬용 메시 스케일 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic|Scale")
    FVector NormalSkillScale = FVector(2.0f);
};

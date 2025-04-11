#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SW_SkillEffectActor.generated.h"

class UNiagaraComponent;
class USoundBase;
class UAudioComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASkillEffectActor : public AActor
{
    GENERATED_BODY()

public:
    ASkillEffectActor();

    /** 외부에서 위치와 회전 초기화 */
    UFUNCTION(BlueprintCallable, Category = "Effect")
    void InitEffect(FVector Location, FRotator Rotation);

protected:
    virtual void BeginPlay() override;

    /** 나이아가라 이펙트 컴포넌트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effect")
    UNiagaraComponent* NiagaraComponent;

    /** 사운드 컴포넌트 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effect")
    UAudioComponent* AudioComponent;

    /** 자동 파괴까지 지속 시간 */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
    float LifeTime = 2.0f;

private:
    FTimerHandle DestroyTimerHandle;

    void DestroySelf();
};

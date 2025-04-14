#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SW_MythSpawnActor.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_MythSpawnActor : public AActor
{
    GENERATED_BODY()

public:
    ASW_MythSpawnActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override; // Tick 함수 추가

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Myth")
    float DamageMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Myth")
    FVector Range = FVector(300.f); // 스킬 범위 반경

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Myth")
    FVector Offset = FVector(0.f, 0.f, 0.f);

    UPROPERTY()
    AActor* OwnerCharacter;

    UPROPERTY()
    float Damage;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;

    UPROPERTY()
    TSet<AActor*> AlreadyHitActors;

private:

    void ApplyDamage();  // 새로 추가된 함수

    bool bHasAppliedDamage = false; // 데미지 적용 플래그 추가
};
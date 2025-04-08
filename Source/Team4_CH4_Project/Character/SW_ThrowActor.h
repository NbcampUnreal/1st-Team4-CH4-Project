#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SW_ThrowActor.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_ThrowActor : public AActor
{
    GENERATED_BODY()

public:
    ASW_ThrowActor();

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent* Collision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UProjectileMovementComponent* Movement;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 20.f;

    UPROPERTY()
    AActor* IgnoredActor;
};
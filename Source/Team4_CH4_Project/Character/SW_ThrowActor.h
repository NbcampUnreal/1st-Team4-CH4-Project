#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SW_ThrowActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_ThrowActor : public AActor
{
    GENERATED_BODY()

public:
    ASW_ThrowActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* MeshComp;
protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* CollisionComp;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
    float MoveSpeed = 2000.f;
     
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
    float LifeSpan = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
    float Damage = 0;

    // 중복 피격 방지용 TSet
    UPROPERTY()
    TSet<AActor*> AlreadyHitActors;

    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void ApplyThrowDamage(AActor* OtherActor);
};
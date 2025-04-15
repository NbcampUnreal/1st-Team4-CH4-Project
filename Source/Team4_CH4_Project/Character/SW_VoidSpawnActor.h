#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SW_VoidSpawnActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_VoidSpawnActor : public AActor
{
    GENERATED_BODY()

public:
    ASW_VoidSpawnActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void")
    float Damage = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void")
    float DamageMultiplier = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void")
    FVector Range = FVector(300.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void")
    FVector Offset = FVector::ZeroVector;

    UPROPERTY()
    AActor* OwnerCharacter;

    UPROPERTY()
    TSet<AActor*> AlreadyHitActors;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;

private:
    void ApplyDamage();
};

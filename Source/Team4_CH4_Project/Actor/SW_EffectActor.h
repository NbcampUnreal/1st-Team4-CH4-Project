// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SW_EffectActor.generated.h"

class USphereComponent;

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASW_EffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void EndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent*
		OtherComp,
		int32 OtherBodyIndex
	);
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};

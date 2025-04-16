// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SW_AN_BrallDirectionNiagara.generated.h"

class UNiagaraSystem;

UCLASS()
class TEAM4_CH4_PROJECT_API USW_AN_BrallDirectionNiagara : public UAnimNotify
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
    FVector LocationOffset = FVector::ZeroVector;

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
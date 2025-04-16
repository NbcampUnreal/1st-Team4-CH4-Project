// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_AN_BrallDirectionNiagara.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

void USW_AN_BrallDirectionNiagara::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!NiagaraEffect || !MeshComp) return;
    AActor* Owner = MeshComp->GetOwner();
    FVector Forward = Owner ? Owner->GetActorForwardVector() : FVector::ForwardVector;
    FVector SpawnLocation = MeshComp->GetComponentLocation()
        + Forward * LocationOffset.Y
        + FVector::UpVector * LocationOffset.Z
        + Owner->GetActorRightVector() * LocationOffset.X;
    FRotator SpawnRotation = Forward.Rotation();
    UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
        NiagaraEffect,
        MeshComp,
        NAME_None, // SocketName (현재 없음)
        SpawnLocation,
        SpawnRotation,
        EAttachLocation::KeepWorldPosition,
        true
    );

    if (NiagaraComp)
    {
        NiagaraComp->SetVectorParameter("User.Direction", Forward); // Niagara 내에서 사용할 변수
    }
}
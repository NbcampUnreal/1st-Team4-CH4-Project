#include "SW_Magic.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ASW_Magic::ASW_Magic()
{
	MoveSpeed = 1500.f;
	CurrentComboIndex = -1; 
	NormalStaticMesh = nullptr;
	NormalSkillMaterial = nullptr;
	NormalSkillNiagara = nullptr;
	Combo1_M = nullptr;
	Combo2_M = nullptr;
	Combo3_M = nullptr;
	ComboEffectNiagara = nullptr;
}

void ASW_Magic::BeginPlay()
{
	Super::BeginPlay();
	ApplyVisualSettings(); // BeginPlay에서도 설정 적용
}


void ASW_Magic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASW_Magic::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;

	if (!OtherActor || OtherActor == this || OtherActor == GetInstigator() || OtherActor == GetOwner())
		return;

	if (AlreadyHitActors.Contains(OtherActor)) return;
	AlreadyHitActors.Add(OtherActor);

	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}

// 나이아가라 생성 함수 분리 (선택적)
void ASW_Magic::SpawnNiagaraEffect(UNiagaraSystem* NiagaraSystem)
{
    UNiagaraFunctionLibrary::SpawnSystemAttached(
        NiagaraSystem,
        MeshComp,
        NAME_None,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::KeepRelativeOffset,
        true
    );
}

void ASW_Magic::ApplyVisualSettings()
{
    if (!MeshComp) return;

    // 메시/머티리얼/나이아가라 설정 (기존 로직)
    if (CurrentComboIndex >= 0) 
    {
        switch (CurrentComboIndex)
        {
        case 0: if (Combo1_M) MeshComp->SetMaterial(0, Combo1_M); break;
        case 1: if (Combo2_M) MeshComp->SetMaterial(0, Combo2_M); break;
        case 2: if (Combo3_M) MeshComp->SetMaterial(0, Combo3_M); break;
        }

        if (ComboEffectNiagara) SpawnNiagaraEffect(ComboEffectNiagara);

        // 콤보 공격 크기 적용
        SetActorScale3D(ComboScale); // 기본 콤보 크기

    }
    else // 노멀 스킬
    {
        if (NormalStaticMesh) MeshComp->SetStaticMesh(NormalStaticMesh);
        if (NormalSkillMaterial) MeshComp->SetMaterial(0, NormalSkillMaterial);
        if (NormalSkillNiagara) SpawnNiagaraEffect(NormalSkillNiagara);

        // 노멀 스킬 크기 적용
        SetActorScale3D(NormalSkillScale); 
    }
}


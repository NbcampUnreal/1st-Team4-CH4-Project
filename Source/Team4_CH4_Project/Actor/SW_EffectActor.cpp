// Fill out your copyright notice in the Description page of Project Settings.


#include "Team4_CH4_Project/Actor/SW_EffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "Team4_CH4_Project/AbilitySystem/SW_AttributeSet.h"

ASW_EffectActor::ASW_EffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ASW_EffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	// bind ASW_EffectActor::OnOverlap to Sphere->OnComponentBeginOverlap
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASW_EffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASW_EffectActor::EndOverlap);
}

// TODO : Change this to apply a Gameplay Effect. For now, using const_cast as a hack.
void ASW_EffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const USW_AttributeSet* SW_AttributeSet = Cast<USW_AttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(USW_AttributeSet::StaticClass()));
		
		USW_AttributeSet* MutableAuraAttributeSet = const_cast<USW_AttributeSet*>(SW_AttributeSet);
		MutableAuraAttributeSet->SetHealth(SW_AttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ASW_EffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


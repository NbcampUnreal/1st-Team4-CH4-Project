// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "Net/UnrealNetwork.h"

// Sets default values
ASW_CharacterBase::ASW_CharacterBase()
	: GroundSpeed(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ASW_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASW_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccelerationLastFrame = Acceleration;
	Acceleration = GetCharacterMovement()->GetCurrentAcceleration();

	VelocityLastFrame = Velocity;
	Velocity = GetCharacterMovement()->Velocity;
}

// Called to bind functionality to input
void ASW_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASW_CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

float ASW_CharacterBase::GetGroundSpeed()
{
	return GroundSpeed;
}

void ASW_CharacterBase::SetGroundSpeed(float _GroundSpeed)
{
	GroundSpeed = _GroundSpeed;
}

bool ASW_CharacterBase::IsMoving() const
{
	if (Acceleration != FVector::ZeroVector && Velocity != FVector::ZeroVector)
	{
		return true;
	}

	return false;
}

bool ASW_CharacterBase::IsJump() const
{
	if (InAir())
	{
		return GetVelocity().Z > 0;
	}
	return false;
}

bool ASW_CharacterBase::InAir() const
{
	return GetCharacterMovement()->IsFalling();
}

UAbilitySystemComponent* ASW_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASW_CharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

//void ASW_CharacterBase::StartDownTime(float DownTime)
//{
//	RemainingTime = DownTime;
//
//	GetWorld()->GetTimerManager().SetTimer(
//		DownTime_TimerHandle,
//		this,
//		&ASW_CharacterBase::UpdateCooldown,
//		1.0f,
//		true
//	);
//}
//
//void ASW_CharacterBase::UpdateCooldown()
//{
//	UE_LOG(LogTemp, Warning, TEXT("%f"), RemainingTime);
//	RemainingTime -= 1.0f;
//	OnDownTimeTick.Broadcast(FMath::CeilToInt(RemainingTime));
//	if (RemainingTime <= 0.f)
//	{
//		GetWorld()->GetTimerManager().ClearTimer(DownTime_TimerHandle);
//	}
//}

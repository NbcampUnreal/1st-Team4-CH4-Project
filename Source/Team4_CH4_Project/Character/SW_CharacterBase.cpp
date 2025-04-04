// Fill out your copyright notice in the Description page of Project Settings.


#include "SW_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SW_PlayerAnimInstance.h"
#include "SW_PlayerAnimLayerInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASW_CharacterBase::ASW_CharacterBase()
	: GroundSpeed(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// 카메라 거리
	CameraBoom->TargetArmLength = 800.f;

	// 카메라를 위로 기울임
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));

	// 고정 시점
	CameraBoom->bUsePawnControlRotation = false;

	// 카메라 설정
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;


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

	DOREPLIFETIME(ASW_CharacterBase, Health);
	DOREPLIFETIME(ASW_CharacterBase, Stamina);
}

void ASW_CharacterBase::Player_Move(const FInputActionValue& _InputValue)
{

}

void ASW_CharacterBase::Player_Jump(const FInputActionValue& _InputValue)
{
	bool IsJump = _InputValue.Get<bool>();
	if (IsJump)
	{
		Jump();
	}
}

void ASW_CharacterBase::ComboAttack()
{
	if (USW_PlayerAnimInstance* Anim = Cast<USW_PlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (Anim->Implements<USW_PlayerAnimLayerInterface>())
		{
			ISW_PlayerAnimLayerInterface::Execute_PlayComboAttack(Anim);
		}
	}
}

void ASW_CharacterBase::JumpAttack()
{
	if (USW_PlayerAnimInstance* Anim = Cast<USW_PlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (Anim->Implements<USW_PlayerAnimLayerInterface>())
		{
			ISW_PlayerAnimLayerInterface::Execute_PlayJumpAttack(Anim);
		}
	}
}

void ASW_CharacterBase::NormalSkill()
{
	if (USW_PlayerAnimInstance* Anim = Cast<USW_PlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (Anim->Implements<USW_PlayerAnimLayerInterface>())
		{
			ISW_PlayerAnimLayerInterface::Execute_PlayNormalSkill(Anim);
		}
	}
}

void ASW_CharacterBase::SpecialSkill()
{
	if (USW_PlayerAnimInstance* Anim = Cast<USW_PlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (Anim->Implements<USW_PlayerAnimLayerInterface>())
		{
			ISW_PlayerAnimLayerInterface::Execute_PlaySpecialSkill(Anim);
		}
	}
}

void ASW_CharacterBase::DashSkill()
{
	if (USW_PlayerAnimInstance* Anim = Cast<USW_PlayerAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (Anim->Implements<USW_PlayerAnimLayerInterface>())
		{
			ISW_PlayerAnimLayerInterface::Execute_PlayDashSkill(Anim);
		}
	}
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

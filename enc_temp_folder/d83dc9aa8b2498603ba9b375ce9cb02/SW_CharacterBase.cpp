#include "SW_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SW_PlayerAnimInstance.h"
#include "SW_PlayerAnimLayerInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASW_CharacterBase::ASW_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 이동속도 관련
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (MoveComp)
	{
		MoveComp->MaxWalkSpeed = 600.f;

		MoveComp->BrakingDecelerationWalking = 2048.f;
		MoveComp->GroundFriction = 8.f;
		MoveComp->MaxAcceleration = 2048.f;
		MoveComp->BrakingFrictionFactor = 2.f;
		MoveComp->BrakingFriction = 8.f;

		MoveComp->bOrientRotationToMovement = true;
		MoveComp->RotationRate = FRotator(0.f, 720.f, 0.f);
		bUseControllerRotationYaw = false;
	}


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 800.f;

	// 카메라 기울임
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
	const FVector2D MoveVector = _InputValue.Get<FVector2D>();
	if (MoveVector.IsNearlyZero())
	{
		return;
	}

	FRotator ControlRotation = GetControlRotation();
	FRotator YawRotation(0, ControlRotation.Yaw, 0);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MoveVector.Y);
	AddMovementInput(RightDirection, MoveVector.X);

}

void ASW_CharacterBase::Player_Jump(const FInputActionValue& _InputValue)
{
	bool IsJump = _InputValue.Get<bool>();
	if (IsJump)
	{
		Jump();
	}
}

// 평타 3타 콤보
void ASW_CharacterBase::ComboAttack()
{
	if (!GetMesh() || !ComboMontages.IsValidIndex(CurrentComboIndex)) return;

	if (bCanNextCombo) 
	{
		UAnimMontage* MontageToPlay = ComboMontages[CurrentComboIndex];
		if (MontageToPlay)
		{
			PlayAnimMontage(MontageToPlay);
			bCanNextCombo = false;

			float MontageDuration = MontageToPlay->GetPlayLength();
			GetWorldTimerManager().SetTimer(
				ComboResetTimer,
				this,
				&ASW_CharacterBase::CheckPendingCombo,
				MontageDuration * 0.9f,
				false
			); 
		}
	}
	else // 평타 도중에 키입력시
	{
		bPendingNextCombo = true;
	}
}

// 점프 공격
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

// 기본 스킬
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

// 궁극기 스킬
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

// 대쉬 스킬
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


// ==============콤보평타관련 함수 모음집==================
void ASW_CharacterBase::ResetCombo()
{
	CurrentComboIndex = 0;
	bCanNextCombo = true;
	bPendingNextCombo = false;
}

void ASW_CharacterBase::CheckPendingCombo()
{
	if (bPendingNextCombo)
	{
		bPendingNextCombo = false;
		CurrentComboIndex++;

		if (!ComboMontages.IsValidIndex(CurrentComboIndex))
		{
			ResetCombo();
			return;
		}

		/* 콤보 몽타주가 너무 많거나 무한 콤보면
		스택 오버플로우나 로직 꼬일 위험 있음.
		아직까지는 평타 몽타주가 3개로 문제는 없어보임 */
		bCanNextCombo = true;
		ComboAttack(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!재귀 호출!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (나중을 위하여)
	}
	else
	{
		ResetCombo();
	}
}

// ======================================================

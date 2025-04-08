#include "SW_Dubu.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "Engine/DamageEvents.h"
#include "InputActionValue.h"

ASW_Dubu::ASW_Dubu()
{
	// 대시 충돌용 박스 콜리전
	DashCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DashCollider"));
	DashCollider->SetupAttachment(RootComponent);
	DashCollider->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	DashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DashCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	DashCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DashCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Dubu::OnDashBoxOverlap);
	DashCollider->SetHiddenInGame(false); // 디버그용
	DashCollider->SetVisibility(true);    // 디버그용

	// 손 콜리전 세팅
	RightHandCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCollider"));
	RightHandCollider->SetupAttachment(GetMesh(), TEXT("R_hand_Jnt"));
	RightHandCollider->SetBoxExtent(FVector(0.5f, 0.3f, 0.3f)); // 콜리전 크기조절
	RightHandCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	RightHandCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RightHandCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Dubu::OnRightHandOverlap);
	RightHandCollider->SetHiddenInGame(false); // 디버그용
	RightHandCollider->SetVisibility(true);   // 디버그용

	LeftHandCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCollider"));
	LeftHandCollider->SetupAttachment(GetMesh(), TEXT("L_hand_Jnt"));
	LeftHandCollider->SetBoxExtent(FVector(0.5f, 0.3f, 0.3f)); //콜리전 크기조절
	LeftHandCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	LeftHandCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LeftHandCollider->OnComponentBeginOverlap.AddDynamic(this, &ASW_Dubu::OnLeftHandOverlap);
	LeftHandCollider->SetHiddenInGame(false); //디버그용
	LeftHandCollider->SetVisibility(true); // 디버그용

	// 콤보 애님 몽타주
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_1.AM_Dubu_Combo_1"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_2.AM_Dubu_Combo_2"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_3.AM_Dubu_Combo_3"));
	if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
	if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
	if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);

	// 체력
	MaxHealth = 700;
	Health = MaxHealth;

	// 기본 스킬
	FSkillData NormalSkillData;
	NormalSkillData.Damage = 20.f;
	NormalSkillData.AttackType = ESkillAttackType::MeleeSphere;
	NormalSkillData.Range = FVector(300.f, 300.f, 300.f); // X: 길이, Y: 폭, Z: 높이
	NormalSkillData.Offset = FVector(100.f, 0.f, 0.f);
	SkillDataMap.Add(FName("NormalSkill"), NormalSkillData);

	// 대시 스킬
	FSkillData DashSkillData;
	DashSkillData.Damage = 35.f;
	DashSkillData.AttackType = ESkillAttackType::MeleeSphere;
	DashSkillData.Range = FVector(300.f);
	DashSkillData.Offset = FVector(250.f, 0.f, 0.f);
	SkillDataMap.Add(FName("DashSkill"), DashSkillData);
}

void ASW_Dubu::BeginPlay()
{
	Super::BeginPlay();
}

// 평타 콤보용 ==================================================================================
// 왼손
void ASW_Dubu::OnRightHandOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
	{
		int32 Damage = 0;

		if (CurrentComboIndex == 0) // 1타
			Damage = 10;
		else if (CurrentComboIndex == 2) // 3타 양손
			Damage = 25;
		else
			return;

		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);

		AlreadyHitActors.Add(OtherActor); //  중복 방지!
	}
}

// 오른손
void ASW_Dubu::OnLeftHandOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
	{
		int32 Damage = 0;

		if (CurrentComboIndex == 1) // 1타
			Damage = 10;
		else if (CurrentComboIndex == 2) // 3타 양손
			Damage = 25;
		else
			return;

		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);

		AlreadyHitActors.Add(OtherActor); //  중복 방지!
	}
}

void ASW_Dubu::RightHandStart()
{
	AlreadyHitActors.Empty(); //  매 콤보마다 초기화
	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASW_Dubu::RightHandEnd()
{
	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASW_Dubu::LeftHandStart()
{
	AlreadyHitActors.Empty(); //  여기서도 초기화
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASW_Dubu::LeftHandEnd()
{
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
// ===========================================================

void ASW_Dubu::DashSkill()
{
	Super::DashSkill();

	FVector DashDirection = GetActorForwardVector().GetSafeNormal();
	float DashSpeed = 2000.f;

	AlreadyHitActors.Empty();
	DashCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 박스 ON

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->BrakingFrictionFactor = 0.f;
	MoveComp->BrakingDecelerationWalking = 0.f;

	LaunchCharacter(DashDirection * DashSpeed, true, true);

	FTimerHandle DashResetHandle;
	GetWorldTimerManager().SetTimer(DashResetHandle, FTimerDelegate::CreateLambda([this, MoveComp]()
		{
			MoveComp->BrakingFrictionFactor = 2.f;
			MoveComp->BrakingDecelerationWalking = 2048.f;

			DashCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 박스 OFF
		}), 0.5f, false);
}

void ASW_Dubu::OnDashBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
	{
		int32 Damage = 35;

		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
		AlreadyHitActors.Add(OtherActor);
	}
}

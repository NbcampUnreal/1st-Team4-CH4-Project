#include "SW_Dubu.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "Engine/DamageEvents.h"
#include "InputActionValue.h"
#include "SW_ThrowActor.h"

ASW_Dubu::ASW_Dubu()
{
	// 리플리케이션 용
	bReplicates = true;
	SetReplicateMovement(true);

	// 체력
	MaxHealth = 700;
	Health = MaxHealth;

	// 기본 데미지
	AttackDamage = 30.f;


	// 대시 충돌용 박스 콜리전
	DashCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DashCollider"));
	DashCollider->SetupAttachment(RootComponent);
	DashCollider->SetBoxExtent(FVector(120.f, 120.f, 100.f));
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

	// 궁극기용 액터 주소
	static ConstructorHelpers::FClassFinder<AActor> ThrowActorBP(TEXT("/Game/Characters/Dubu/BP_ThrowGround/BP_ThrowActor.BP_ThrowActor"));
	if (ThrowActorBP.Succeeded()) ThrowActorClass = ThrowActorBP.Class;

	// 2단 점프용 애니메이션 몽타주 주소
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpStartMontage(TEXT("/Game/Characters/Dubu/Animation/Win_or_Lose/Win_Animation/AM_2StepJump.AM_2StepJump"));
	if (JumpStartMontage.Succeeded())
	{
		SkillMontages.Add(FName("Dubu_JumpAttackStart"), JumpStartMontage.Object);
	}

	// 콤보 애님 몽타주
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_1.AM_Dubu_Combo_1"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_2.AM_Dubu_Combo_2"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Dubu/Animation/ComboAttack/AM_Dubu_Combo_3.AM_Dubu_Combo_3"));
	if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
	if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
	if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);

	// 기본 스킬
	FSkillData NormalSkillData;
	NormalSkillData.DamageMultiplier = 1.5f; // 데미지 계수
	NormalSkillData.AttackType = ESkillAttackType::MeleeBox;
	NormalSkillData.Range = FVector(300.f, 300.f, 300.f); // X: 길이, Y: 폭, Z: 높이
	NormalSkillData.Offset = FVector(100.f, 0.f, 0.f); // 캐릭터 스킬 방향
	SkillDataMap.Add(FName("NormalSkill"), NormalSkillData);

	// 점프 공격
	FSkillData JumpAttackData;
	JumpAttackData.DamageMultiplier = 2.f; // 데미지 계수
	JumpAttackData.AttackType = ESkillAttackType::MeleeBox;
	JumpAttackData.Range = FVector(200.f, 200.f, 200.f);  // X: 길이, Y: 폭, Z: 높이
	JumpAttackData.Offset = FVector(0.f); // 캐릭터 스킬 방향
	SkillDataMap.Add(FName("JumpAttack"), JumpAttackData);
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
		if (!HasAuthority()) return; 

		int32 Damage = FMath::RoundToInt(AttackDamage * 1.f);

		if (CurrentComboIndex == 0) // 1타
			Damage = Damage * 1;
		else if (CurrentComboIndex == 2) // 3타 양손 
			Damage = Damage * 1 + 20;
		else
			return;

		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);

		AlreadyHitActors.Add(OtherActor); //  중복 방지
	}
}

// 오른손
void ASW_Dubu::OnLeftHandOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !AlreadyHitActors.Contains(OtherActor))
	{
		if (!HasAuthority()) return; 

		int32 Damage = AttackDamage;

		if (CurrentComboIndex == 1) // 1타
			Damage = Damage * 1;
		else if (CurrentComboIndex == 2) // 3타 양손
			Damage = Damage * 1 + 20;
		else
			return;

		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);

		AlreadyHitActors.Add(OtherActor); //  중복 방지
	}
}

void ASW_Dubu::RightHandStart()
{
	if (!HasAuthority()) return; 

	AlreadyHitActors.Empty(); //  매 콤보마다 초기화
	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASW_Dubu::RightHandEnd()
{
	RightHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASW_Dubu::LeftHandStart()
{
	if (!HasAuthority()) return;

	AlreadyHitActors.Empty(); //  여기서도 초기화
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASW_Dubu::LeftHandEnd()
{
	LeftHandCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
// ===========================================================================================



// 대쉬 스킬용 ================================================================================
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
		int32 Damage = FMath::RoundToInt(AttackDamage * 1.5f);

		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
		AlreadyHitActors.Add(OtherActor);
	}
}
// ===========================================================================================



// 점프 공격용 =================================================================================
void ASW_Dubu::JumpAttack()
{
	if (bIsLocked) return;

	bIsJumpAttacking = true;

	// 45도 위 방향
	FVector Forward = GetActorForwardVector() * 0.707f;
	FVector Up = FVector::UpVector * 0.707f;
	FVector JumpDir = (Forward + Up).GetSafeNormal();

	// 중력 OFF + 점프 시작
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->GravityScale = 0.f;
	LaunchCharacter(JumpDir * 1000.f, true, true);

	// 점프 애니메이션 재생
	PlaySkillAnimation(FName("Dubu_JumpAttackStart"));

	// 0.3초 후 25도 각도로 낙하
	FTimerHandle DiveTimer;
	GetWorldTimerManager().SetTimer(DiveTimer, FTimerDelegate::CreateLambda([this]()
		{
			UCharacterMovementComponent* MoveComp = GetCharacterMovement();

			MoveComp->StopMovementImmediately(); // 멈춤
			MoveComp->GravityScale = 1.f;        // 중력 ON

			// 25도 낙하 방향
			FVector Forward = GetActorForwardVector() * 0.9063f;
			FVector Down = FVector::DownVector * 0.4226f;
			FVector DiveDir = (Forward + Down).GetSafeNormal();

			// 낙하 속도
			LaunchCharacter(DiveDir * 1200.f, true, true);

			// 낙하 시 애니메이션 재생
			PlaySkillAnimation(FName("JumpAttack"));

		}), 0.3f, false);
}
// ===========================================================================================



// 궁극기 스킬용 ==============================================================================
void ASW_Dubu::ThrowUltimateSkill()
{
	if (!HasAuthority()) return;

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = this;

	auto* Thrown = GetWorld()->SpawnActor<ASW_ThrowActor>(ThrowActorClass, SpawnLocation, SpawnRotation, Params);
	if (Thrown)
	{
		Thrown->Damage = AttackDamage * 8.f;
	}
}
// ========================================================================================== =
#include "SW_Brall.h"
#include "GameFramework/CharacterMovementComponent.h"

ASW_Brall::ASW_Brall()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo1(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo1.AM_Brall_Combo1"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo2(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo2.AM_Brall_Combo2"));
    static ConstructorHelpers::FObjectFinder<UAnimMontage> Combo3(TEXT("/Game/Characters/Brall/Animation/ComboAttack/AM_Brall_Combo3.AM_Brall_Combo3"));

    if (Combo1.Succeeded()) ComboMontages.Add(Combo1.Object);
    if (Combo2.Succeeded()) ComboMontages.Add(Combo2.Object);
    if (Combo3.Succeeded()) ComboMontages.Add(Combo3.Object);
}

void ASW_Brall::BeginPlay()
{
    Super::BeginPlay();
}

void ASW_Brall::DashSkill()
{
    Super::DashSkill();

    GetWorldTimerManager().SetTimer(
        DashTimerHandle,
        this,
        &ASW_Brall::ExecuteDesh,
        0.3f,
        false
    );
}

void ASW_Brall::ExecuteDesh()
{
    FVector DashDirection = GetActorForwardVector().GetSafeNormal();
    float DashSpeed = 2000.f;

    UCharacterMovementComponent* MoveComp = GetCharacterMovement();
    MoveComp->BrakingFrictionFactor = 0.f;
    MoveComp->BrakingDecelerationWalking = 0.f; 

    LaunchCharacter(DashDirection * DashSpeed, true, true);

    FTimerHandle DashResetHandle;
    GetWorldTimerManager().SetTimer(DashResetHandle, FTimerDelegate::CreateLambda([=]()
        {
            MoveComp->BrakingFrictionFactor = 2.f;
            MoveComp->BrakingDecelerationWalking = 2048.f;
        }), 0.5f, false);
}
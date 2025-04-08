#include "SW_SkillAnimNotify.h"
#include "SW_CharacterBase.h"
#include "SW_Dubu.h"
#include "SW_Brall.h"

void USkillAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (AActor* Owner = MeshComp->GetOwner())
    {
        if (ASW_CharacterBase* Character = Cast<ASW_CharacterBase>(Owner))
        {
            if (NotifyEventName == "BeginSkill")
            {
                Character->SetLockedState(true); // 전체 입력 차단
            }
            else if (NotifyEventName == "EndSkill")
            {
                Character->SetLockedState(false); // 전체 입력 해제
            }
            else if (NotifyEventName == "ApplyDamage")
            {
                if (SkillName.IsNone()) return;

                TArray<AActor*> Targets = Character->GetTargetsInRange(SkillName);
                Character->ApplySkillDamage(SkillName, Targets);
            }

           // 캐릭터 콤보용 노티파이
            else if (NotifyEventName == "ComboInput")
            {
                Character->bCanNextCombo = true; // 콤보 입력 가능
            }

            // 근접캐릭터 평타시 앞으로가는 거리
            else if (NotifyEventName == "DoForwardMove")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    FVector Forward = Dubu->GetActorForwardVector();
                    Dubu->LaunchCharacter(Forward * 800.f, true, false);
                }
                else if (ASW_Brall* Brall = Cast<ASW_Brall>(Character))
                {
                    FVector Forward = Brall->GetActorForwardVector();
                    Brall->LaunchCharacter(Forward * 1000.f, true, false);
                }
            }
            // 두부 평타 노티파이
            else if (NotifyEventName == "RightHandStart")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->SetMovementLocked(true); // 이동만 멈춤
                    Dubu->RightHandStart();
                }
            }
            else if (NotifyEventName == "RightHandEnd")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->SetMovementLocked(false); // 이동 재개
                    Dubu->RightHandEnd();
                }
            }
            else if (NotifyEventName == "LeftHandStart")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->SetMovementLocked(true); // 이동만 멈춤
                    Dubu->LeftHandStart();
                }
            }
            else if (NotifyEventName == "LeftHandEnd")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->SetMovementLocked(false); // 이동 재개
                    Dubu->LeftHandEnd();
                }
            }

            else if (NotifyEventName == "ThrowActor")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    if (Dubu->ThrowActorClass)
                    {
                        FVector SpawnLocation = Dubu->GetActorLocation() + Dubu->GetActorForwardVector() * 100.f;
                        FRotator SpawnRotation = Dubu->GetActorRotation();

                        FActorSpawnParameters SpawnParams;
                        SpawnParams.Owner = Dubu;
                        SpawnParams.Instigator = Dubu->GetInstigator();

                        AActor* ThrownActor = Dubu->GetWorld()->SpawnActor<AActor>(
                            Dubu->ThrowActorClass,
                            SpawnLocation,
                            SpawnRotation,
                            SpawnParams
                        );
                    }
                }
            }

            // 브랄 평타 노티파이
            else if (NotifyEventName == "SwordStart")
            {
                if (ASW_Brall* Brall = Cast<ASW_Brall>(Character))
                {
                    Brall->SetMovementLocked(true); // 이동만 멈춤
                    Brall->SwordAttackStart();
                }
            }
            else if (NotifyEventName == "SwordEnd")
            {
                if (ASW_Brall* Brall = Cast<ASW_Brall>(Character))
                {
                    Brall->SetMovementLocked(false); // 이동 재개
                    Brall->SwordAttackEnd();
                }
            }
        }
    }
}
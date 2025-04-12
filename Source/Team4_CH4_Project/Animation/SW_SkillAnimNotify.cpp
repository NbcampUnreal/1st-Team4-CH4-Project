#include "SW_SkillAnimNotify.h"
#include "SW_CharacterBase.h"
#include "SW_Dubu.h"
#include "SW_Brall.h"
#include "SW_Myth.h"
#include "SW_ThrowActor.h"

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

            // 공격이 적용되는 노티파이
            else if (NotifyEventName == "ApplyDamage")
            {
                if (Character->HasAuthority()) // 서버에서만 실행
                {
                    Character->Server_ApplySkillDamage(SkillName);
                }
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

            // 두부 궁극기 스킬
            else if (NotifyEventName == "ThrowActor")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->ThrowUltimateSkill();
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

            else if (NotifyEventName == "FireArrow")
            {
                if (ASW_Myth* Myth = Cast<ASW_Myth>(Character))
                {
                    Myth->SpawnArrow();
                }
            }

            else if (NotifyEventName == "FireComboArrow")
            {
                if (ASW_Myth* Myth = Cast<ASW_Myth>(Character))
                {
                    Myth->SpawnComboArrow();
                }
            }
        }
    }
}
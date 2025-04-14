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
                Character->SetLockedState(true);     // 전체 인풋 차단
                Character->bComboInputActive = false;
                Character->bComboQueued = false;
            }
            else if (NotifyEventName == "EndSkill")
            {
                Character->SetLockedState(false);
                Character->bComboInputActive = false;

                if (Character->bComboQueued)
                {
                    Character->bComboQueued = false;
                    Character->AdvanceCombo(); // 다음 콤보 실행
                }
                else
                {
                    Character->ResetCombo();   // 종료
                }
            }

            // 스킬 공격이 적용되는 노티파이 (스킬이름을 잘 넣어주어야한다.)
            else if (NotifyEventName == "ApplyDamage")
            {
                if (Character->HasAuthority()) // 서버에서만 실행
                {
                    Character->Server_ApplySkillDamage(SkillName);
                }
            }

            else if (NotifyEventName == "ComboInput")
            {
                Character->bComboInputActive = true; // 콤보 입력 허용 타이밍
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

            // 두부 궁극기 스킬
            else if (NotifyEventName == "ThrowActor")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->ThrowUltimateSkill();
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
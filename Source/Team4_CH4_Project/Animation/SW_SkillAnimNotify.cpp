#include "SW_SkillAnimNotify.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SW_CharacterBase.h"
#include "SW_Dubu.h"
#include "SW_Brall.h"
#include "SW_Myth.h"
#include "SW_Void.h"
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

            // 근접캐릭터 평타시 바라보는곳으로 500만큼 이동 
            else if (NotifyEventName == "DoForwardMove")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    UCharacterMovementComponent* MoveComp = Dubu->GetCharacterMovement();

                    MoveComp->BrakingFrictionFactor = 0.f;
                    MoveComp->BrakingDecelerationWalking = 0.f;

                    FVector Forward = Dubu->GetActorForwardVector();
                    Dubu->LaunchCharacter(Forward * 1000.f, true, true); // Z도 override

                    MoveComp->bIgnoreBaseRotation = true;

                    FTimerHandle ResetHandle;
                    Dubu->GetWorldTimerManager().SetTimer(ResetHandle, [Dubu]()
                        {
                            if (IsValid(Dubu))
                            {
                                UCharacterMovementComponent* MoveComp = Dubu->GetCharacterMovement();
                                MoveComp->BrakingFrictionFactor = 2.f;
                                MoveComp->BrakingDecelerationWalking = 2048.f;
                            }
                        }, 0.2f, false);
                }
                else if (ASW_Brall* Brall = Cast<ASW_Brall>(Character))
                {
                    UCharacterMovementComponent* MoveComp = Brall->GetCharacterMovement();

                    MoveComp->BrakingFrictionFactor = 0.f;
                    MoveComp->BrakingDecelerationWalking = 0.f;

                    FVector Forward = Brall->GetActorForwardVector();
                    Brall->LaunchCharacter(Forward * 1000.f, true, true); // Z도 override

                    MoveComp->bIgnoreBaseRotation = true;

                    FTimerHandle ResetHandle;
                    Brall->GetWorldTimerManager().SetTimer(ResetHandle, [Brall]()
                        {
                            if (IsValid(Brall))
                            {
                                UCharacterMovementComponent* MoveComp = Brall->GetCharacterMovement();
                                MoveComp->BrakingFrictionFactor = 2.f;
                                MoveComp->BrakingDecelerationWalking = 2048.f;
                            }
                        }, 0.2f, false);
                }
            }

            // 원거리 Myth 캐릭터 대쉬 스킬시 뒤로 1400만큼 이동
            else if (NotifyEventName == "DoBackwardMove")
            {
                if (ASW_Myth* Myth = Cast<ASW_Myth>(Character))
                {
                    UCharacterMovementComponent* MoveComp = Myth->GetCharacterMovement();

                    MoveComp->BrakingFrictionFactor = 0.f;
                    MoveComp->BrakingDecelerationWalking = 0.f;

                    // 루트모션 무시하고 이동 강제 적용
                    FVector Backward = -Myth->GetActorForwardVector();
                    Myth->LaunchCharacter(Backward * 2000.f, true, true); // Z도 override

                    // 루트모션 끄기 (애니메이션에서 꺼도 되지만 코드로 강제로 껐음)
                    MoveComp->bIgnoreBaseRotation = true;

                    FTimerHandle ResetHandle;
                    Myth->GetWorldTimerManager().SetTimer(ResetHandle, [Myth]()
                        {
                            if (IsValid(Myth))
                            {
                                UCharacterMovementComponent* MoveComp = Myth->GetCharacterMovement();
                                MoveComp->BrakingFrictionFactor = 2.f;
                                MoveComp->BrakingDecelerationWalking = 2048.f;
                            }
                        }, 0.2f, false);
                }
            }

            // 두부 궁극기 스킬 노티파이
            else if (NotifyEventName == "ThrowActor")
            {
                if (ASW_Dubu* Dubu = Cast<ASW_Dubu>(Character))
                {
                    Dubu->ThrowUltimateSkill();
                }
            }

            // myth 노멀스킬 노티파이
            else if (NotifyEventName == "FireArrow")
            {
                if (ASW_Myth* Myth = Cast<ASW_Myth>(Character))
                {
                    bool bIsNormalSkill = SkillName == "NormalSkill";
                    Myth->SpawnArrow(true, bIsNormalSkill);
                }
                }

            else if (NotifyEventName == "FireComboArrow")
            {
                if (ASW_Myth* Myth = Cast<ASW_Myth>(Character))
                {
                    Myth->SpawnComboArrow();
                }
            }

            // void 기본콤보어택 발사체 노티파이
            else if (NotifyEventName == "FireComboMagic")
            {
                if (ASW_Void* Void = Cast<ASW_Void>(Character))
                {
                    Void->SpawnComboMagic();
                }
}
            // void 노말스킬 발사용 노티파이
            else if (NotifyEventName == "FireNormalMagic")
            {
                if (ASW_Void* Void = Cast<ASW_Void>(Character))
                {
                    Void->SpawnNormalMagic();
                }
}

            // void 대쉬스킬용 노티파이
            else if (NotifyEventName == "DoDashTeleport")
            {
                if (ASW_Void* Void = Cast<ASW_Void>(Character))
                {
                    Void->ExecuteDashTeleport();
                }
}


        }
    }
}
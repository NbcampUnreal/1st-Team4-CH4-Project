#include "SW_SkillAnimNotify.h"
#include "SW_CharacterBase.h"

void USkillAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (AActor* Owner = MeshComp->GetOwner())
    {
        if (ASW_CharacterBase* Character = Cast<ASW_CharacterBase>(Owner))
        {
            if (NotifyEventName == "BeginSkill")
            {
                Character->SetLockedState(true);
            }
            else if (NotifyEventName == "EndSkill")
            {
                Character->SetLockedState(false);
                Character->CheckPendingCombo(); 
            }
        }
    }
}

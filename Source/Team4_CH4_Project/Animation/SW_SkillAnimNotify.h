#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SW_SkillAnimNotify.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USkillAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

public:
    // Notify 종류: BeginSkill, EndSkill, ApplyDamage 등
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNotify")
    FName NotifyEventName;

    // 데미지를 줄 때 어떤 스킬로 처리할지 지정 (SkillDataMap의 키와 일치해야 함)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNotify")
    FName SkillName;

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

#if WITH_EDITOR
    virtual FString GetNotifyName_Implementation() const override
    {
        return FString::Printf(TEXT("%s [%s]"), *NotifyEventName.ToString(), *SkillName.ToString());
    }
#endif
};

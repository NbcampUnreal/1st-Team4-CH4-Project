#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SW_SkillAnimNotify.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API USkillAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNotify")
    FName NotifyEventName;

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

#if WITH_EDITOR
    virtual FString GetNotifyName_Implementation() const override
    {
        return NotifyEventName.ToString();
    }
#endif
};

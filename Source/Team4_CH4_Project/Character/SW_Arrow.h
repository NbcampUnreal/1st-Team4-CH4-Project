#pragma once

#include "CoreMinimal.h"
#include "SW_ThrowActor.h"
#include "SW_Arrow.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Arrow : public ASW_ThrowActor
{
	GENERATED_BODY()

public:
	ASW_Arrow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Myth")
	TSubclassOf<AActor> SpawnActorClass;

	UPROPERTY()
	AActor* OwnerCharacter;
};

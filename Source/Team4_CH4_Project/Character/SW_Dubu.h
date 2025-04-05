#pragma once

#include "CoreMinimal.h"
#include "SW_CharacterBase.h"
#include "SW_Dubu.generated.h"

UCLASS()
class TEAM4_CH4_PROJECT_API ASW_Dubu : public ASW_CharacterBase
{
	GENERATED_BODY()
	
public:
	ASW_Dubu();

public:
	virtual void BeginPlay() override;
	virtual void DashSkill() override;


	// ↑↑↑↑↑↑↑↑↑↑↑↑↑↑변수↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	//===================================
	// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓함수↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

};

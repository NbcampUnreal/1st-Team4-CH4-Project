#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SW_GameMode.generated.h"

class USW_TestCharacterClassInfo;


UCLASS()
class TEAM4_CH4_PROJECT_API ASW_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	ASW_GameMode();
	
	USW_TestCharacterClassInfo* GetCharacterClassDefaultInfo() const;

	// 게임 종료 후 표시할 결과창 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> ResultWidgetClass;

	void HandleGameOver();
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category= "Custom Values|Class Defaults")
	TObjectPtr<USW_TestCharacterClassInfo> ClassDefaults;

	virtual void OnPostLogin(AController* NewPlayer) override;

	void ShowResultWidget();
	bool bGameOverHandled;

};

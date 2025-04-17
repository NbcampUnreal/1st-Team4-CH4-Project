
#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "../GameData/SW_ResultData.h"
#include "SW_ResultsViewModel.generated.h"


UCLASS()
class TEAM4_CH4_PROJECT_API USW_ResultsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetPlayTimeSeconds() const { return PlayTimeSeconds; };
	UFUNCTION(BlueprintCallable)
	void SetPlayTimeSeconds(const int32& Seconds);
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetPlayTimeText() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	bool GetHasWon() const { return HasWon; };
	UFUNCTION(BlueprintCallable)
	void SetHasWon(const bool& bHasWon);

	UFUNCTION(BlueprintPure, FieldNotify)
	FSW_ResultData GetResultToAdd() const { return ResultToAdd; };
	UFUNCTION(BlueprintCallable)
	void SetResultToAdd(const FSW_ResultData& InData);

private:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	int32 PlayTimeSeconds;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	bool HasWon;
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter, meta = (AllowPrivateAccess))
	FSW_ResultData ResultToAdd;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SW_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TEAM4_CH4_PROJECT_API USW_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	USW_AttributeSet();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AT, Category = "Vital Attributes")
	FGameplayAttributeData AT;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, AT);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DF, Category = "Vital Attributes")
	FGameplayAttributeData DF;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, DF);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_H_DownTime, Category = "Sikll Attributes")
	FGameplayAttributeData H_DownTime;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, H_DownTime);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_J_DownTime, Category = "Sikll Attributes")
	FGameplayAttributeData J_DownTime;
	ATTRIBUTE_ACCESSORS(USW_AttributeSet, J_DownTime);


	// vital
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& Old_Health) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& Old_MaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& Old_Mana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& Old_MaxMana) const;

	UFUNCTION()
	void OnRep_AT(const FGameplayAttributeData& Old_AT) const;

	UFUNCTION()
	void OnRep_DF(const FGameplayAttributeData& Old_DF) const;

	// skill
	UFUNCTION()
	void OnRep_H_DownTime(const FGameplayAttributeData& Old_Q_DownTime) const;

	UFUNCTION()
	void OnRep_J_DownTime(const FGameplayAttributeData& Old_R_DownTime) const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "PracticeAttributeSet.generated.h"

class IPawnUIInterface;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/*
 * CachedPawnUIInterface
 * : 위젯 등에 값의 변화를 브로드캐스팅 하기 위한 UIComponent의 인터페이스 변수
 */
UCLASS()
class PRACTICE_API UPracticeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPracticeAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;	

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, AttackPower)
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Ult")
	FGameplayAttributeData CurrentUlt;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, CurrentUlt)

	UPROPERTY(BlueprintReadOnly, Category = "Ult")
	FGameplayAttributeData MaxUlt;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, MaxUlt)

	UPROPERTY(BlueprintreadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, DamageTaken)

	UPROPERTY(BlueprintReadOnly, Category = "Exp")
	FGameplayAttributeData MaxExp;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, MaxExp)

	UPROPERTY(BlueprintReadOnly, Category = "Exp")
	FGameplayAttributeData CurrentExp;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, CurrentExp)

	UPROPERTY(BlueprintreadOnly, Category = "Exp")
	FGameplayAttributeData ExpTaken;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, ExpTaken)
	
	UPROPERTY(BlueprintReadOnly, Category = "Bullets")
	FGameplayAttributeData CurrentBullets;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, CurrentBullets)

	UPROPERTY(BlueprintReadOnly, Category = "Bullets")
	FGameplayAttributeData MaxBullets;
	ATTRIBUTE_ACCESSORS(UPracticeAttributeSet, MaxBullets)

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;

};

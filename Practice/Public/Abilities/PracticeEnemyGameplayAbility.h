// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "PracticeEnemyGameplayAbility.generated.h"

class APracticeEnemyCharacter;
class UEnemyCombatComponent;
/*
* FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InDamageFloat): Enemy용 DamageEffectSpecHandle 생성 함수
*/
UCLASS()
class PRACTICE_API UPracticeEnemyGameplayAbility : public UPracticeGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Practice|Ability")
	APracticeEnemyCharacter* GetEnemyCharacterFromActorInfo(); 

	UFUNCTION(BlueprintPure, Category = "Practice|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Practice|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InDamageFloat);
	
private:
	TWeakObjectPtr<APracticeEnemyCharacter> CachedPracticeEnemyCharacter;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "PracticeSoldierGameplayAbility.generated.h"

class APracticeSoldierCharacter;
class APracticePlayerController;
class USoldierCombatComponent;
/**
 * FGameplayEffectSpecHandle MakeSoldierDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InDamageFloat)
 * : Soldier클래스 전용 DamageEffectSpecHandle 생성 함수
 */
UCLASS()
class PRACTICE_API UPracticeSoldierGameplayAbility : public UPracticeGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Soldier|Ability")
	APracticeSoldierCharacter* GetSoldierCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soldier|Ability")
	APracticePlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soldier|Ability")
	USoldierCombatComponent* GetSoldierCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Soldier|Ability")
	FGameplayEffectSpecHandle MakeSoldierDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InDamageFloat);

private:
	TWeakObjectPtr<APracticeSoldierCharacter> CachedPracticeSoldierCharacter;
	TWeakObjectPtr<APracticePlayerController> CachedPracticePlayerController;
};

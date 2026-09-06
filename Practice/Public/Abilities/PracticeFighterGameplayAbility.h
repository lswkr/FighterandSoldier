// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "PracticeFighterGameplayAbility.generated.h"

class APracticeFighterCharacter;
class APracticePlayerController;
class UFighterCombatComponent;
/**
 * FGameplayEffectSpecHandle MakeFighterDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
 * : Fighter클래스 전용 DamageEffectSpecHandle생성함수
 */
UCLASS()
class PRACTICE_API UPracticeFighterGameplayAbility : public UPracticeGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category= "Fighter|Ability")
	APracticeFighterCharacter* GetFighterCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Fighter|Ability")
	APracticePlayerController* GetPlayerControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Fighter|Ability")
	UFighterCombatComponent* GetFighterCombatComponentFromActorInfo();


	UFUNCTION(BlueprintPure, Category = "Fighter|Ability")
	FGameplayEffectSpecHandle MakeFighterDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
	
private:
	//위의 함수들은 Cast가 필요한데 저 함수들이 호출될 때마다 Cast할 필요없도록 한 번 호출된 이후 저장시키는 변수
	TWeakObjectPtr<APracticeFighterCharacter> CachedPracticeFighterCharacter;
	
	//위와 같은 이유로 Player의 컨트롤러를 저장하는 변수
	TWeakObjectPtr<APracticePlayerController> CachedPracticePlayerController;
	
};

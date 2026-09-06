// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PracticeTypes/PracticeStructTypes.h"
#include "PracticeAbilitySystemComponent.generated.h"


/*
 * 아래 두 함수는 Fighter, Soldier의 SetupPlayerInputComponent에서 콜백 함수로 설정된다.
 * 
 * void OnAbilityInputPressed(const FGameplayTag& InInputTag)
 * : InInputTag에 해당하는 어빌리티의 버튼을 눌렸을 때의 로직 
 * 
 * void OnAbilityInputReleased(const FGameplayTag& InInputTag)
 * : InInputTag에 해당하는 어빌리티의 버튼을 땠을 때의 로직
 * 
 * 	void GrantSoldierGunAbilities(const TArray<FPracticeAbilitySet>& InGunAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OunGrantedAbilitySpecHandles)
 * : Gun을 획득했을 때 Gun클래스에 있는 어빌리티들을 ASC에 넣는 함수
 * 
 * void RemoveGrantedSoldierGunAbilities(UPARAM(Ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
 * : Gun이 교체될 때 ASC에 있던 어빌리티들을 제거하는 함수
 * 
 * bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
 * : Tag로 그에 해당되는 어빌리티를 Activate시키는 함수
 * 
 * int32 LevelingUpAbilities()
 * : 캐릭터가 레벨업했을 때 어빌리티의 레벨을 올리는 함수. AttributeSet에서 Exp의 값이 바뀔 때 호출된다.
 */

UCLASS()
class PRACTICE_API UPracticeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	
	void OnAbilityInputPressed(const FGameplayTag& InInputTag); 
	void OnAbilityInputReleased(const FGameplayTag& InInputTag); 
	
	UFUNCTION(BlueprintCallable, Category="Practice|Ability", meta = (ApplyLevel="1"))
	void GrantSoldierGunAbilities(const TArray<FPracticeAbilitySet>& InGunAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OunGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Practice|Ability")
	void RemoveGrantedSoldierGunAbilities(UPARAM(Ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category="Practice|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);

	UFUNCTION(BlueprintCallable,Category= "Practice|Ability")
	int32 LevelingUpAbilities();
};

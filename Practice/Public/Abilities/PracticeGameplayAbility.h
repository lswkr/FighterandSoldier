// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PracticeTypes/PracticeEnumTypes.h"
#include "PracticeGameplayAbility.generated.h"

class UPawnCombatComponent;
class UPracticeAbilitySystemComponent;
class APracticeBaseCharacter;

/**
 * EPracticeAbilityActivationPolicy: 어빌리티 종류
 * OnTriggered: Trigger할 때 발동되는 어빌리티
 * OnGiven: ASC에 들어갈 때 발동되는 어빌리티
 */
UENUM(BlueprintType)
enum class EPracticeAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/*
* FGameplayEffectSpecHandle MakeExpEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InExpFloat)
* : 경험치(Exp) 이펙트 스펙핸들 함수. 
*/

UCLASS()
class PRACTICE_API UPracticeGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly, Category = "PracticeAbility")
	EPracticeAbilityActivationPolicy AbilityActivationPolicy = EPracticeAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Practice|Ability")
	APracticeBaseCharacter* GetPawnCharacterFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Practice|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Practice|Ability")
	UPracticeAbilitySystemComponent* GetPracticeAbilitySystemComponentFromActorInfo() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Practice|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EPracticeSuccessType& OutSuccessType);

	UFUNCTION(BlueprintPure, Category = "Practice|Ability")
	virtual FGameplayEffectSpecHandle MakeExpEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InExpFloat);


};

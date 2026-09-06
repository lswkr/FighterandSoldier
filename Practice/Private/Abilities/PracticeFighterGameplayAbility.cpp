// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PracticeFighterGameplayAbility.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Character/PracticeFighterCharacter.h"
#include "Controller/PracticePlayerController.h"
#include "PracticeGameplayTags.h"


APracticeFighterCharacter* UPracticeFighterGameplayAbility::GetFighterCharacterFromActorInfo()
{
	if (!CachedPracticeFighterCharacter.IsValid())
	{
		CachedPracticeFighterCharacter = Cast<APracticeFighterCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPracticeFighterCharacter.IsValid() ? CachedPracticeFighterCharacter.Get() : nullptr;
}

APracticePlayerController* UPracticeFighterGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPracticePlayerController.IsValid())
	{
		CachedPracticePlayerController = Cast<APracticePlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPracticePlayerController.IsValid() ? CachedPracticePlayerController.Get() : nullptr;
}

UFighterCombatComponent* UPracticeFighterGameplayAbility::GetFighterCombatComponentFromActorInfo()
{
	return GetFighterCharacterFromActorInfo()->GetFighterCombatComponent();
}

FGameplayEffectSpecHandle UPracticeFighterGameplayAbility::MakeFighterDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetPracticeAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetPracticeAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		PracticeGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	
	return EffectSpecHandle;
}





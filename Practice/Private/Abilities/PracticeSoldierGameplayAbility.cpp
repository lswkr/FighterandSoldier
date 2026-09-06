// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PracticeSoldierGameplayAbility.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Controller/PracticePlayerController.h"
#include "PracticeGameplayTags.h"

APracticeSoldierCharacter* UPracticeSoldierGameplayAbility::GetSoldierCharacterFromActorInfo()
{
	if (!CachedPracticeSoldierCharacter.IsValid())
	{
		CachedPracticeSoldierCharacter = Cast<APracticeSoldierCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPracticeSoldierCharacter.IsValid() ? CachedPracticeSoldierCharacter.Get() : nullptr;
}

APracticePlayerController* UPracticeSoldierGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPracticePlayerController.IsValid())
	{
		CachedPracticePlayerController = Cast<APracticePlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPracticePlayerController.IsValid() ? CachedPracticePlayerController.Get() : nullptr;
}

USoldierCombatComponent* UPracticeSoldierGameplayAbility::GetSoldierCombatComponentFromActorInfo()
{
	return GetSoldierCharacterFromActorInfo()->GetSoldierCombatComponent();
}

FGameplayEffectSpecHandle UPracticeSoldierGameplayAbility::MakeSoldierDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InDamageFloat)
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
		InDamageFloat
	);

	return EffectSpecHandle;
}


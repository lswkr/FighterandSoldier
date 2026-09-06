// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PracticeEnemyGameplayAbility.h"
#include "Character/PracticeEnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "PracticeGameplayTags.h"

APracticeEnemyCharacter* UPracticeEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!CachedPracticeEnemyCharacter.IsValid())
    {
        CachedPracticeEnemyCharacter = Cast<APracticeEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }
    return CachedPracticeEnemyCharacter.IsValid()? CachedPracticeEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UPracticeEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UPracticeEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InDamageFloat)
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
	); //GEExecCalc_DamageTaken에서 활용
    return EffectSpecHandle;
}

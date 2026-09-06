// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PracticeGameplayAbility.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/PracticeBaseCharacter.h"
#include "PracticeGameplayTags.h"

void UPracticeGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EPracticeAbilityActivationPolicy::OnGiven) //OnGiven이면 
	{
		if (ActorInfo && !Spec.IsActive()) 
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle); //바로 실행
		}
	}
}

void UPracticeGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EPracticeAbilityActivationPolicy::OnGiven) //OnGiven이면 
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);//끝났을 때 ASC에서 바로 제거
		}
	}
}

APracticeBaseCharacter* UPracticeGameplayAbility::GetPawnCharacterFromActorInfo() const
{
	return  Cast<APracticeBaseCharacter> (GetAvatarActorFromActorInfo());
}

UPawnCombatComponent* UPracticeGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UPracticeAbilitySystemComponent* UPracticeGameplayAbility::GetPracticeAbilitySystemComponentFromActorInfo() const
{
	return Cast<UPracticeAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UPracticeGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(InSpecHandle.IsValid());
	check(TargetASC);
	

	return GetPracticeAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UPracticeGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EPracticeSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EPracticeSuccessType::Successful : EPracticeSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

FGameplayEffectSpecHandle UPracticeGameplayAbility::MakeExpEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InExpFloat)
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
		PracticeGameplayTags::Shared_SetByCaller_BaseExp,
		InExpFloat
	);

	return EffectSpecHandle;
}

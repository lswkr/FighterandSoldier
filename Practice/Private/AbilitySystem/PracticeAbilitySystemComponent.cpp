// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "PracticeGameplayTags.h"
#include "Abilities/PracticeGameplayAbility.h"

#include "PracticeDebugHelper.h"

void UPracticeAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag) 
{
	
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTag(InInputTag) && !AbilitySpec.IsActive())
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UPracticeAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()  || !InInputTag.MatchesTag(PracticeGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTag(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UPracticeAbilitySystemComponent::GrantSoldierGunAbilities(const TArray<FPracticeAbilitySet>& InGunAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OunGrantedAbilitySpecHandles)
{
	if (InGunAbilities.IsEmpty())
	{
		return;
	}
	
	for (const FPracticeAbilitySet& AbilitySet : InGunAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
	
		OunGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UPracticeAbilitySystemComponent::RemoveGrantedSoldierGunAbilities(UPARAM(Ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}

bool UPracticeAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);
	
	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num()-1);

		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];
		
		check(SpecToActivate);
		
		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	return false;
}

int32 UPracticeAbilitySystemComponent::LevelingUpAbilities()
{
	int32 LevelResult = 1;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		AbilitySpec.Level++;
		LevelResult = AbilitySpec.Level;
	}
	return LevelResult;
}

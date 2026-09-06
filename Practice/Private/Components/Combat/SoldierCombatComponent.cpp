// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/SoldierCombatComponent.h"
#include "PracticeTypes/PracticeStructTypes.h"
#include "Items/Weapons/PracticeGunBase.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Components/BoxComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PracticeGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "PracticeDebugHelper.h"

void USoldierCombatComponent::DeleteCurrentGun(FGameplayTag InGunTagToDelete)
{
	if (!CharacterCarriedGunMap.Contains(InGunTagToDelete)) {
		return;
	}

	CharacterCarriedGunMap.Remove(InGunTagToDelete); 
	return;
}

APracticeGunBase* USoldierCombatComponent::GetCharacterCarriedGunByTag(FGameplayTag InGunTagToGet) const
{
	if (CharacterCarriedGunMap.Contains(InGunTagToGet)) {
		if (APracticeGunBase* const* FoundGun = CharacterCarriedGunMap.Find(InGunTagToGet))
		{
			return *FoundGun;
		}
	}
	return nullptr;
}

APracticeGunBase* USoldierCombatComponent::GetCharacterCurrentEquippedGun() const
{
	if (!CurrentEquippedGunTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedGunByTag(CurrentEquippedGunTag);
}

float USoldierCombatComponent::GetSoldierCurrentEquippedGunDamageAtLevel(float InLevel) const
{
	return GetCharacterCurrentEquippedGun()->GunData.GunBaseDamage.GetValueAtLevel(InLevel);
}

void USoldierCombatComponent::RegisterNewGun(FGameplayTag InGunTagToRegister, APracticeGunBase* InGunToRegister)
{
	check(InGunToRegister);

	if (CharacterCarriedGunMap.Contains(InGunTagToRegister))
	{
		return;
	}
	
	if (CharacterCarriedGunMap.Contains(CurrentEquippedGunTag))
	{	
		GetCharacterCarriedGunByTag(CurrentEquippedGunTag)->DetachFromActor(FDetachmentTransformRules(FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true),false));
		GetCharacterCarriedGunByTag(CurrentEquippedGunTag)->Destroy();
		DeleteCurrentGun(CurrentEquippedGunTag);
	}

	CharacterCarriedGunMap.Emplace(InGunTagToRegister, InGunToRegister);
	CurrentEquippedGunTag = InGunTagToRegister;
}

void USoldierCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (!CachedPracticeSoldierCharacter.IsValid())
	{
		CachedPracticeSoldierCharacter = Cast<APracticeSoldierCharacter>(GetOwningPawn());
	}
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		PracticeGameplayTags::Shared_Event_MeleeHit,
		Data
	);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		PracticeGameplayTags::Player_Shared_Event_HitPause,
		FGameplayEventData()
	);

}

void USoldierCombatComponent::OnHitBoxPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		PracticeGameplayTags::Player_Shared_Event_HitPause,
		FGameplayEventData()
	);
}

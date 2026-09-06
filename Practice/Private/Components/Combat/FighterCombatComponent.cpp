// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/FighterCombatComponent.h"
#include "Components/BoxComponent.h"
#include "Character/PracticeFighterCharacter.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PracticeGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "PracticeDebugHelper.h"



void UFighterCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (!CachedPracticeFighterCharacter.IsValid())
	{
		CachedPracticeFighterCharacter = Cast<APracticeFighterCharacter>(GetOwningPawn());
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

void UFighterCombatComponent::OnHitBoxPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		PracticeGameplayTags::Player_Shared_Event_HitPause,
		FGameplayEventData()
	);
}

//void UFighterCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
//{
//	/*APracticeFighterCharacter* OwningFighterCharacter = GetOwningPawn<APracticeFighterCharacter>();
//	
//	check(OwningFighterCharacter);
//
//	UBoxComponent* LeftCollisionBox = OwningFighterCharacter->GetLeftCollisionBox();
//	UBoxComponent* RightCollisionBox = OwningFighterCharacter->GetRightCollisionBox();
//
//	switch (ToggleDamageType)
//	{
//	case EToggleDamageType::Left:
//		LeftCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
//		break;
//	case EToggleDamageType::Right:
//		RightCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
//		break;
//	default:
//		break;
//	}
//	if (!bShouldEnable)
//	{
//		OverlappedActors.Empty();
//	}*/
//}

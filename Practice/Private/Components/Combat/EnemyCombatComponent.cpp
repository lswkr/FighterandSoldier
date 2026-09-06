// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "Character/PracticeEnemyCharacter.h"
#include "PracticeGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<APracticeEnemyCharacter>(GetOwningPawn());
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
}

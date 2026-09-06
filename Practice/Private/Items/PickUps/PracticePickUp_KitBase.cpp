// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/PracticePickUp_KitBase.h"
#include "GameFramework/Actor.h"
#include "Items/Weapons/PracticeGunBase.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Character/PracticeFighterCharacter.h"
#include "Components/Combat/SoldierCombatComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "PracticeGameplayTags.h"
#include "GameplayEffect.h"

#include "PracticeDebugHelper.h"
void APracticePickUp_KitBase::Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(KitGameplayEffectClass);

	UGameplayEffect* EffectCDO = KitGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	); //설정된 게임플레이 이펙트를 적용시킨다.

	BP_OnKitConsumed();
}


void APracticePickUp_KitBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APracticeSoldierCharacter* OverlappedSoldierCharacter = Cast<APracticeSoldierCharacter>(OtherActor))
	{
		OverlappedSoldierCharacter->GetPracticeAbilitySystemComponent()->TryActivateAbilityByTag(PracticeGameplayTags::Player_Shared_Ability_PickUp);
	}
	
	else if (APracticeFighterCharacter* OverlappedFighterCharacter = Cast<APracticeFighterCharacter>(OtherActor))
	{
		OverlappedFighterCharacter->GetPracticeAbilitySystemComponent()->TryActivateAbilityByTag(PracticeGameplayTags::Player_Shared_Ability_PickUp);
	}
}

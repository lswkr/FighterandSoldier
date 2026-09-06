// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/PracticePickUp_GunBase.h"
#include "GameFramework/Actor.h"
#include "Items/Weapons/PracticeGunBase.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Components/Combat/SoldierCombatComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "PracticeGameplayTags.h"

#include "PracticeDebugHelper.h"

void APracticePickUp_GunBase::Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	if (APracticeSoldierCharacter* PracticeSoldierCharacter = Cast<APracticeSoldierCharacter>(AbilitySystemComponent->GetAvatarActor()))
	{
		
		if (APracticeGunBase* Gun = Cast<APracticeGunBase>(PracticeGun->ClassDefaultObject))
		{
			BP_OnGunConsumed();
		} 
	}
	
}

TSubclassOf<APracticeGunBase> APracticePickUp_GunBase::GetGunClass()
{
	return PracticeGun;
}

FGameplayTag APracticePickUp_GunBase::GetGunTag()
{
	return GunTag;
}

void APracticePickUp_GunBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APracticeSoldierCharacter* OverlappedSoldierCharacter = Cast<APracticeSoldierCharacter>(OtherActor))
	{
		OverlappedSoldierCharacter->GetPracticeAbilitySystemComponent()->TryActivateAbilityByTag(PracticeGameplayTags::Player_Shared_Ability_PickUp);
	}
}

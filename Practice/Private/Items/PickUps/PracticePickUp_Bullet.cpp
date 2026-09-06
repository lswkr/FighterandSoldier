// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/PracticePickUp_Bullet.h"
#include "GameFramework/Actor.h"
#include "Items/Weapons/PracticeGunBase.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Components/Combat/SoldierCombatComponent.h"
#include "Character/PracticeSoldierCharacter.h"
#include "PracticeGameplayTags.h"


void APracticePickUp_Bullet::Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	BP_OnBulletConsumed();
}

void APracticePickUp_Bullet::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APracticeSoldierCharacter* OverlappedSoldierCharacter = Cast<APracticeSoldierCharacter>(OtherActor))
	{
		OverlappedSoldierCharacter->GetPracticeAbilitySystemComponent()->TryActivateAbilityByTag(PracticeGameplayTags::Player_Shared_Ability_PickUp);
	}
}

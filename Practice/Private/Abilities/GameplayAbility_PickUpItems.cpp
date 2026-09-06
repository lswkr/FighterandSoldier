// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GameplayAbility_PickUpItems.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Items/PickUps/PracticePickUp_GunBase.h"
#include "Character/PracticeBaseCharacter.h"
#include "PracticeGameplayTags.h"
#include "Items/PickUps/PracticePickUp_KitBase.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Components/Combat/SoldierCombatComponent.h"
#include "Items/Weapons/PracticeGunBase.h"
#include "Items/PickUps/PracticePickUp_Bullet.h"
#include "Items/PickUps/PracticePickUp_KitBase.h"

#include "PracticeDebugHelper.h"

void UGameplayAbility_PickUpItems::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbility_PickUpItems::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_PickUpItems::CollectItems()
{
	CollectedItems.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPawnCharacterFromActorInfo(),
		GetPawnCharacterFromActorInfo()->GetActorLocation(),
		GetPawnCharacterFromActorInfo()->GetActorLocation()+-GetPawnCharacterFromActorInfo()->GetActorUpVector()*BoxTraceDistance,
		TraceBoxSize/2.f,
		(-GetPawnCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		ItemTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape? EDrawDebugTrace::ForOneFrame: EDrawDebugTrace::None,
		TraceHits,
		true
	);

	/*Cast활용이 많이 일어나 추후 다른 방식으로 업데이트 필요*/
	for (const FHitResult& TraceHit : TraceHits) 
	{
		if (APracticePickUp_GunBase* FoundGun = Cast<APracticePickUp_GunBase>(TraceHit.GetActor())) //총인 경우
		{
			CollectedItems.AddUnique(FoundGun); 
		}
		else if (APracticePickUp_Bullet* FoundBullet = Cast<APracticePickUp_Bullet>(TraceHit.GetActor())) //총알인 경우
		{
			CollectedItems.AddUnique(FoundBullet);
		}
		else if (APracticePickUp_KitBase* FoundKit = Cast<APracticePickUp_KitBase>(TraceHit.GetActor())) //체력 키트인 경우
		{
			CollectedItems.AddUnique(FoundKit);
		}
	}
	
	/*아무것도 감지되지 않았다면 어빌리티 Cancel*/
	if (CollectedItems.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}

}

void UGameplayAbility_PickUpItems::ConsumeItems()
{
	if (CollectedItems.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	/*아래에서 활용되는 Consume()함수는 PickUps폴더에 있는 파일들 참조*/
	for (APracticePickUpBase* CollectedItem : CollectedItems)
	{
		if (CollectedItem->GetItemType().MatchesTagExact(PracticeGameplayTags::Item_Gun))
		{
			APracticePickUp_GunBase* GunItem = Cast<APracticePickUp_GunBase>(CollectedItem);
			BP_OnConsumeGun(GunItem->GetGunTag());
			GunItem->Consume(GetPracticeAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
		else if (CollectedItem->GetItemType().MatchesTagExact(PracticeGameplayTags::Item_Kit))
		{
			BP_OnConsumeKit();
			CollectedItem->Consume(GetPracticeAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
		else if (CollectedItem->GetItemType().MatchesTagExact(PracticeGameplayTags::Item_Bullet))
		{
			APracticePickUp_Bullet* Bullet = Cast<APracticePickUp_Bullet>(CollectedItem);
			if (APracticeSoldierCharacter* SoldierCharacter = Cast<APracticeSoldierCharacter>(GetPawnCharacterFromActorInfo()))
			{
				if (SoldierCharacter->GetSoldierCombatComponent()->GetCharacterCurrentEquippedGun()) 
				{
					BP_OnConsumeBullets(SoldierCharacter->GetSoldierCombatComponent()->GetCharacterCurrentEquippedGun()->GunData.GunTag);
					Bullet->Consume(GetPracticeAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
				}
			
			}
		}
	}
	
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/PracticePickUpBase.h"
#include "PracticePickUp_Bullet.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API APracticePickUp_Bullet : public APracticePickUpBase
{
	GENERATED_BODY()
	
public:

	virtual void Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) override;

protected:
	//PickUp_GunBase와 함께 SoldierClass에게만 반응하도록 하는 함수. PickupAbility를 일으킨다.
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	//Consume됐을 때 호출될 함수. Blueprint로 구현되어있으며 기본적으로 소리발생 및 Destroy
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Bullet Consumed"))
	void BP_OnBulletConsumed();
};

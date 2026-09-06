// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/PracticePickUpBase.h"
#include "PracticePickUp_KitBase.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class PRACTICE_API APracticePickUp_KitBase : public APracticePickUpBase
{
	GENERATED_BODY()

public:
	virtual void Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) override;

	//Cosume했을 때 수행시킬 함수. Blueprint로 구현했으며 기본적으로 sound를 만들고 Destroy수행
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Kit Consumed"))
	void BP_OnKitConsumed();

protected:
	//오버랩되면 Fighter, Soldier 둘 다에게 PickUpAbility를 발동시키는 함수.
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly) //Consume했을 때 적용될 GameplayEffect
	TSubclassOf<UGameplayEffect> KitGameplayEffectClass;

	
};

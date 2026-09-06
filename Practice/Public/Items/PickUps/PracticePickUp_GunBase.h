// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/PracticePickUpBase.h"
#include "PracticePickUp_GunBase.generated.h"

class APracticeGunBase;
class APracticeSoldierCharacter;
/**
 * 
 */
UCLASS()
class PRACTICE_API APracticePickUp_GunBase : public APracticePickUpBase
{
	GENERATED_BODY()
	
public:
	virtual void Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel) override;

	UFUNCTION(BlueprintPure)
	TSubclassOf<APracticeGunBase> GetGunClass();

	UFUNCTION(BlueprintPure)
	FGameplayTag GetGunTag();

	//Consume됐을 때 호출될 함수. Blueprint로 구현되어있으며 기본적으로 소리발생 및 Destroy
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Gun Consumed"))
	void BP_OnGunConsumed();

protected:
	//Gun종류는 Soldier클래스만 반응하도록
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	//아래는 Soldier캐릭터에 Gun을 장착시킬 때 필요한 총의 정보들
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
	TSubclassOf<APracticeGunBase> PracticeGun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag GunTag;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "GameplayAbility_PickUpItems.generated.h"

class APracticePickUpBase;

/* 
 * void CollectItems(): ExecuteTaskOnTick(AbilityTask_ExecuteTaskOnTick파일 참조)에서 아이템 획득 전까지 Tick마다 호출되는 로직
 * void ConsumeItems(): ExecuteTaskOnTick 도중 아이템 획득 버튼을 눌렸을 때 실행되는 로직
 */

UCLASS()
class PRACTICE_API UGameplayAbility_PickUpItems : public UPracticeGameplayAbility
{
	GENERATED_BODY()
	
public:
	//BlueprintImplementableEvent
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnConsumeGun(FGameplayTag GunTypeTag); 

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnConsumeKit();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnConsumeBullets(FGameplayTag GunTypeTag);


protected:
	//~Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	//~End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void CollectItems();

	UFUNCTION(BlueprintCallable)
	void ConsumeItems();

private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f; 

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> ItemTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape = false; //디버깅 도형 그리기 부울 변수

	UPROPERTY()
	TArray<APracticePickUpBase*> CollectedItems;
};

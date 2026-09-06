// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UPracticeEnemyGameplayAbility;

/**
 * Enemy만의 Ability를 가지는 DataAsset
 */
UCLASS()
class PRACTICE_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UPracticeEnemyGameplayAbility>> EnemyCombatAbilities;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UPracticeGameplayAbility;
class UPracticeAbilitySystemComponent;

class UGameplayEffect;
/**
 * 어빌리티, 초기화 게임플레이 이펙트를 가지는 DataAsset.
 * 캐릭터들의 PossesedBy에서 GiveToAbilitySystemComponent함수를 통해 이를 ASC에 전달하게된다.
 */
UCLASS()
class PRACTICE_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

	virtual void OnLevelUp(UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPracticeGameplayAbility>> AcivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPracticeGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
	
	void GrantAbilities(const TArray<TSubclassOf<UPracticeGameplayAbility>>& InAbilitiesToGive, UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "PracticeTypes/PracticeStructTypes.h"
#include "DataAsset_FighterStartUpData.generated.h"





/**
 * Input을 통해 발동되는 Player들의 Ability를 함께 가지는 DataAsset 
 * Soldier캐릭터가 작업이 어느 정도 진행된 이후 추가되면서 이름이 현재가 되었다.
 * 적용시킬 때에는 별 문제 없음
 */
UCLASS()
class PRACTICE_API UDataAsset_FighterStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FPracticeAbilitySet> PracticeFighterAbilitySets;
};

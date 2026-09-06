// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "PracticeBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UPracticeBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const; //특정 태그 가질 때 다른 애니메이션으로 바꾸기 위해사용하는 함수(Blend By Bool에서 사용) 
};

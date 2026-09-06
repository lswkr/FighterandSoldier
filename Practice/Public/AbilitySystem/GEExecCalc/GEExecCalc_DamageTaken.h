// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_DamageTaken.generated.h"

/*
 * DamageEffectSpecHandle 생성 시 사용되는 GEExecCalc클래스
 * 상대방의 DefensePower와 자신의 AttackPower데미지를 바탕으로 DamageTaken을 계산해주는 로직이다. 
 */

UCLASS()
class PRACTICE_API UGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEExecCalc_DamageTaken();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

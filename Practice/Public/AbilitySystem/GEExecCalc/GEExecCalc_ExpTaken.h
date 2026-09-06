// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_ExpTaken.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UGEExecCalc_ExpTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UGEExecCalc_ExpTaken();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};

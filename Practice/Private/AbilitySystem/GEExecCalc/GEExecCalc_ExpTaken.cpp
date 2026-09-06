// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_ExpTaken.h"

#include "AbilitySystem/PracticeAttributeSet.h"
#include "PracticeGameplayTags.h"

#include "PracticeDebugHelper.h"

struct FPracticeExpCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(ExpTaken)

	FPracticeExpCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPracticeAttributeSet, ExpTaken, Source, false)
	}
};

static FPracticeExpCapture& GetPracticeExpCapture()
{
	static FPracticeExpCapture PracticeExpCapture;
	return PracticeExpCapture;
}

UGEExecCalc_ExpTaken::UGEExecCalc_ExpTaken()
{
	RelevantAttributesToCapture.Add(GetPracticeExpCapture().ExpTakenDef);
}

void UGEExecCalc_ExpTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float BaseExp = 0.f;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(PracticeGameplayTags::Shared_SetByCaller_BaseExp))
		{
			BaseExp = TagMagnitude.Value;

		}
	}
	/* 적들의 MaxHealth를 바탕으로 Exp를 계산 */
	const float FinalExpDone = BaseExp / 10.f; 
	if (FinalExpDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetPracticeExpCapture().ExpTakenProperty,
				EGameplayModOp::Override,
				FinalExpDone
			)
		);
	}
}

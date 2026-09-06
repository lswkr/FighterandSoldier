// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/PracticeAttributeSet.h"
#include "PracticeGameplayTags.h"

struct FPracticeDamageCapture //¾îÆ®¸®ºäÆ® Ä¸Ã³
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FPracticeDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPracticeAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPracticeAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPracticeAttributeSet, DamageTaken, Source, false)
	}
};

static const FPracticeDamageCapture& GetPracticeDamageCapture()
{
	static FPracticeDamageCapture PracticeDamageCapture;
	return PracticeDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetPracticeDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetPracticeDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetPracticeDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPracticeDamageCapture().AttackPowerDef, EvaluateParameters,SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes) 																					
	{
		if (TagMagnitude.Key.MatchesTagExact(PracticeGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(PracticeGameplayTags::Shared_SetByCaller_AttackType_ComboAttack))
		{
			UsedComboCount = TagMagnitude.Value;
		}
		
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPracticeDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	if (UsedComboCount != 0)
	{
		const float DamageIncreasePercent = (UsedComboCount - 1) * 0.05 + 1.f;

		BaseDamage *= DamageIncreasePercent;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier( 
			FGameplayModifierEvaluatedData(
				GetPracticeDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
	
}

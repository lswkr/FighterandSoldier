// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeTypes/PracticeStructTypes.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"

bool FPracticeAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

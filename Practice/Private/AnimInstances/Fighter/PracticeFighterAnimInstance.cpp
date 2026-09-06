// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Fighter/PracticeFighterAnimInstance.h"
#include "Character/PracticeFighterCharacter.h"

void UPracticeFighterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningFighterCharacter = Cast<APracticeFighterCharacter>(OwningCharacter);
	}
}

void UPracticeFighterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

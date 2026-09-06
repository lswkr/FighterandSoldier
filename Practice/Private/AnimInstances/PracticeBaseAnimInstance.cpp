// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/PracticeBaseAnimInstance.h"
#include "PracticeFunctionLibrary.h"

bool UPracticeBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return UPracticeFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
    }
    return false;
}

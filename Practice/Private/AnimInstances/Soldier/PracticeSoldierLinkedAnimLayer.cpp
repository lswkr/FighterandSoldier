// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Soldier/PracticeSoldierLinkedAnimLayer.h"
#include "AnimInstances/Soldier/PracticeSoldierAnimInstance.h"

UPracticeSoldierAnimInstance* UPracticeSoldierLinkedAnimLayer::GetSoldierAnimInstance() const
{
    return Cast<UPracticeSoldierAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

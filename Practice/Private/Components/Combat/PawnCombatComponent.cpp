// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Components/BoxComponent.h"
#include "Character/PracticeBaseCharacter.h"

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnHitBoxPulledFromTargetActor(AActor* InteractedActor)
{
}

void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	APracticeBaseCharacter* OwningPracticeBaseCharacter = GetOwningPawn<APracticeBaseCharacter>();

	check(OwningPracticeBaseCharacter);

	UBoxComponent* LeftCollisionBox = OwningPracticeBaseCharacter->GetLeftCollisionBox();
	UBoxComponent* RightCollisionBox = OwningPracticeBaseCharacter->GetRightCollisionBox();
	UBoxComponent* FootCollisionBox = OwningPracticeBaseCharacter->GetFootCollisionBox();
	switch (ToggleDamageType)
	{
	case EToggleDamageType::Left:
		LeftCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::Right:
		RightCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::Foot:
		FootCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}
	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}

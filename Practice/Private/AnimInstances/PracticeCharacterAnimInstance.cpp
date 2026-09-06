// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/PracticeCharacterAnimInstance.h"
#include "Character/PracticeBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

void UPracticeCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<APracticeBaseCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UPracticeCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	const FTransform Transform = OwningCharacter->GetActorTransform();
	FVector Velocity = OwningCharacter->GetVelocity();

	FVector AngleVector = UKismetMathLibrary::InverseTransformDirection(Transform, Velocity);

	Angle = UKismetMathLibrary::MakeRotFromX(AngleVector).Yaw;

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}

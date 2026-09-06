// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Soldier/PracticeSoldierAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PracticeSoldierCharacter.h"
//float UPracticeSoldierAnimInstance::GetAimPitch() const
//{
//    if (APawn* Pawn = TryGetPawnOwner()) 
//    {
//        return UKismetMathLibrary::NormalizedDeltaRotator(Pawn->GetActorRotation(), Pawn->GetControlRotation()).Pitch;
//    }
//    return 0;
//}

void UPracticeSoldierAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningSoldierCharacter = Cast<APracticeSoldierCharacter>(OwningCharacter);//OwningCharacter는 Base, OwningHeroCharacter는 Hero. 이렇게 Casting하는 방식으로 몬스터 애님도 사용할듯
	}
}

void UPracticeSoldierAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!OwningCharacter || !OwningMovementComponent) {
		return;
	}
	AimPitchAngle = -UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacter->GetActorRotation(), OwningCharacter->GetControlRotation()).Pitch;
}

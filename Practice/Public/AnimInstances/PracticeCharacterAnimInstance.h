// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PracticeBaseAnimInstance.h"
#include "PracticeCharacterAnimInstance.generated.h"

class APracticeBaseCharacter;
class UCharacterMovementComponent;
/*
 * void NativeThreadSafeUpdateAnimation(float DeltaSeconds)
 * : 프레임마다의 각도, 속도 변화를 가지고 애니메이션 업데이트에 활용
 */
UCLASS()
class PRACTICE_API UPracticeCharacterAnimInstance : public UPracticeBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	APracticeBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float Angle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;

};

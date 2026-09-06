// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PracticeCharacterAnimInstance.h"
#include "PracticeSoldierAnimInstance.generated.h"

class APracticeSoldierCharacter;
/*
 * float AimPitchAngle: Soldier는 상,하 에임 이동이 가능. 각도 AimOffset각도 조절 변수
 */
UCLASS()
class PRACTICE_API UPracticeSoldierAnimInstance : public UPracticeCharacterAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	APracticeSoldierCharacter* OwningSoldierCharacter;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess="true"))
	float AimPitchAngle;
	
};

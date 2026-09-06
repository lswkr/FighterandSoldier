// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PracticeCharacterAnimInstance.h"
#include "PracticeFighterAnimInstance.generated.h"

class APracticeFighterCharacter;
/**
 * NativeInitializeAnimation: OwningCharacter¿˙¿Â
 */
UCLASS()
class PRACTICE_API UPracticeFighterAnimInstance : public UPracticeCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	APracticeFighterCharacter* OwningFighterCharacter;


};

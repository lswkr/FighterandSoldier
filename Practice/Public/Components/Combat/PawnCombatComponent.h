// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"


/*
 * EToggleDamageType
 * : 콜리전 박스가 붙는 위치에 대한 Enum
 */

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	Left,
	Right,
	Foot
};

/**
 * void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
 * : 콜리전 박스의 콜리전을 켜고 끄는 함수. 애니메이션 몽타주에서 활용된다.
 */
UCLASS()
class PRACTICE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnHitBoxPulledFromTargetActor(AActor* InteractedActor);

protected:
	UFUNCTION(BlueprintCallable, Category = "Practice|Combat")
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	TArray<AActor*> OverlappedActors;
};

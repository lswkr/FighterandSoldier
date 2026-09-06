// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "FighterCombatComponent.generated.h"

class APracticeFighterCharacter;


/*
 *  virtual void OnHitTargetActor(AActor* HitActor) 
 *  : Character에서 CollisionBox가 오버랩 됐을 때 호출되는 함수
 *	
 *	virtual void OnHitBoxPulledFromTargetActor(AActor* InteractedActor)
 *	: Character에서 CollisionBox의 오버랩이 끝났을 때 호출되는 함수 
 */

UCLASS()
class PRACTICE_API UFighterCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnHitTargetActor(AActor* HitActor) override;	
															
	virtual void OnHitBoxPulledFromTargetActor(AActor* InteractedActor) override; 
	
private:
	TWeakObjectPtr<APracticeFighterCharacter> CachedPracticeFighterCharacter;
};

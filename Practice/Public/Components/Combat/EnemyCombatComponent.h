// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

class APracticeEnemyCharacter;

/*
 * 	void OnHitTargetActor(AActor* HitActor)
 *  : Character에서 CollisionBox가 오버랩 됐을 때 호출되는 함수
 */

UCLASS()
class PRACTICE_API UEnemyCombatComponent : public UPawnCombatComponent
{

	GENERATED_BODY()

public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

private:
	TWeakObjectPtr<APracticeEnemyCharacter> CachedEnemyCharacter;
};

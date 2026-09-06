// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PracticeBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "PracticeEnemyCharacter.generated.h"


class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;
class UBoxComponent;

/**
 * void InitEnemyStartUpData()
 * : CharacterStartUpData의 비동기 로딩을 위해 활용.
 * 
 * void BeginPlay()
 * : 위젯 초기화에 활용
 */
UCLASS()
class PRACTICE_API APracticeEnemyCharacter : public APracticeBaseCharacter
{
	GENERATED_BODY()

public:
	APracticeEnemyCharacter();

	//~Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetUPawnCombatComponent() const override;
	//~End IPawnCombatInterface Interface

	//~Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	//~End IPawnUIInterface Interface
	

protected:

	virtual void BeginPlay() override;

	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~End APawn Interface


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	void InitEnemyStartUpData(); 

	FGameplayTag TypeTag;

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent;}
};

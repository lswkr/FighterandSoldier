// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "GameplayTagContainer.h"
#include "PracticeBaseCharacter.generated.h"

class UPracticeAbilitySystemComponent;
class UPracticeAttributeSet;
class UDataAsset_StartUpDataBase;
class UBoxComponent;
class UMotionWarpingComponent;

/*
 * void ApplyEffectLevelUp(int32 NewLevel)
 * : 레벨업마다 StartUpData에 있던 초기화 Effect들을 레벨에 맞춰 적용(Fighter,Soldier에서 override)
 *
 *	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
 * : 클래스마다 다른 스켈레탈메시의 본에 콜리전 박스를 붙이기 위해 활용되는 함수
 * 
 * void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
 * : 몸에 붙은 콜리전 박스가 오버랩 됐을 때 콜백되는 함수. 공격 시 데미지 전달을 위해 활용
 * 
 * void OnBodyCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
 * : 콜리전 박스의 오버랩이 끝났을 때 콜백되는 함수. 공격 끝나고 HitPause등을 일으키기 위해 활용
 */
UCLASS()
class PRACTICE_API APracticeBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()
	
public:

	APracticeBaseCharacter();

	//~Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface Interface

	//~Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetUPawnCombatComponent() const override;
	//~End IPawnCombatInterface Interface

	//~Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~End IPawnUIInterface Interface

	virtual void Tick(float DeltaTime) override;

	virtual void ApplyEffectLevelUp(int32 NewLevel);

protected:
	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~End APawn Interface

#if WITH_EDITOR
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface.
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* LeftCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName LeftCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* RightCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName RightCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* FootCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName FootCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UPracticeAbilitySystemComponent* PracticeAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UPracticeAttributeSet* PracticeAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnBodyCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UPracticeAbilitySystemComponent* GetPracticeAbilitySystemComponent() const { return PracticeAbilitySystemComponent; }

	FORCEINLINE UPracticeAttributeSet* GetPracticeAttributeSet() const { return PracticeAttributeSet; }

	FORCEINLINE UBoxComponent* GetLeftCollisionBox() const { return LeftCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightCollisionBox() const { return RightCollisionBox; }
	FORCEINLINE UBoxComponent* GetFootCollisionBox() const { return FootCollisionBox; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FGameplayTag TypeTag;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FGameplayTag GetTypeTag() const { return TypeTag; }
};

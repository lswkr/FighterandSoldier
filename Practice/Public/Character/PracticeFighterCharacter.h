// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PracticeBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "Scalablefloat.h"
#include "PracticeFighterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UBoxComponent;
struct FInputActionValue;
class UFighterCombatComponent;
class UFighterUIComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

/**
 * void Input_Jump(const FInputActionValue& InputActionValue)
 * : 점프사용할 일이 없어 주석처리. 점프가 필요하게 될 때 사용
 * 
 * void Input_PickUpItemsStarted(const FInputActionValue& InputActionValue) 
 * : PickupItem클래스의 인스턴스에 닿았을 때만 발동 가능. 아이템을 줍는 기능을 하는 Event를 보내는 콜백함수이다.
 */
UCLASS()
class PRACTICE_API APracticeFighterCharacter : public APracticeBaseCharacter
{
	GENERATED_BODY()

public:
	APracticeFighterCharacter();

	//~Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetUPawnCombatComponent() const override;
	//~End IPawnCombatInterface Interface

	//~Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UFighterUIComponent* GetFighterUIComponent() const override;
	//~End IPawnUIInterface Interface

	virtual void ApplyEffectLevelUp(int32 NewLevel) override;

protected:
	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~End APawn Interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnBodyCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	

private:

	FGameplayTag TypeTag;
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UFighterCombatComponent* FighterCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UFighterUIComponent* FighterUIComponent;

#pragma endregion 

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	//void Input_Jump(const FInputActionValue& InputActionValue);

	void Input_PickUpItemsStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag); 

#pragma endregion

public:
	FORCEINLINE UFighterCombatComponent* GetFighterCombatComponent() const { return FighterCombatComponent; }
};

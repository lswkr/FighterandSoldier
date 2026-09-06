// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "PracticePickUpBase.generated.h"

class USphereComponent;
class UPracticeAbilitySystemComponent;

//주울 수 있는 Item들의 Base

UCLASS()
class PRACTICE_API APracticePickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APracticePickUpBase();

	virtual void Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

	FGameplayTag GetItemType();

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Interaction")
	USphereComponent* PickUpCollisionSphere;

	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag ItemType; //Gun, Kit, Bullet

private:
	UPROPERTY(EditDefaultsOnly, Category="Component")
	UStaticMeshComponent* StaticMeshComponent;



};

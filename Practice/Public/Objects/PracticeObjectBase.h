// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PracticeObjectBase.generated.h"

class UBoxComponent;

//부술 수 있는 오브젝트. 사용 시 SubtractDurability를 가지고 오브젝트의 내구도를 파괴하도록 디자인 했으나 사용되지는 않음. 
UCLASS()
class PRACTICE_API APracticeObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APracticeObjectBase();

	UFUNCTION(BlueprintCallable)
	void SubtractDurability(float InDamage);

	UFUNCTION(BlueprintCallable)
	float GetDurability() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Component")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	float Durability = 100;
};

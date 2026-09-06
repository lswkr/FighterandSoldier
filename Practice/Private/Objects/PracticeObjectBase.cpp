// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/PracticeObjectBase.h"
#include "Components/BoxComponent.h"

// Sets default values
APracticeObjectBase::APracticeObjectBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
}

void APracticeObjectBase::SubtractDurability(float InDamage)
{
	Durability -= InDamage;
	if (Durability <= 0) 
	{
		Destroy();
	}
	return;
}

float APracticeObjectBase::GetDurability() const
{
	return Durability;
}


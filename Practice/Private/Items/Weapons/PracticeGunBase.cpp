// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/PracticeGunBase.h"

// Sets default values
APracticeGunBase::APracticeGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunMesh;

}

void APracticeGunBase::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> APracticeGunBase::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}



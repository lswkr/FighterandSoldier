// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/PracticePickUpBase.h"
#include "Components/SphereComponent.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"

#include "PracticeDebugHelper.h"
// Sets default values
APracticePickUpBase::APracticePickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.0f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickUpCollisionSphereBeginOverlap);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void APracticePickUpBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void APracticePickUpBase::Consume(UPracticeAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
}

FGameplayTag APracticePickUpBase::GetItemType()
{
	return ItemType;
}





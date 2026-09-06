// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/PracticePayloadRoadBase.h"
#include "Components/SplineComponent.h"

// Sets default values
APracticePayloadRoadBase::APracticePayloadRoadBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);

}

USplineComponent* APracticePayloadRoadBase::GetSplineComponent() const
{
	return SplineComponent;
}

//// Called when the game starts or when spawned
//void APracticePayloadRoadBase::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void APracticePayloadRoadBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//

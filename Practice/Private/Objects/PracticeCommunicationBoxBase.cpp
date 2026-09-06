// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/PracticeCommunicationBoxBase.h"
#include "Components/BoxComponent.h"

// Sets default values
APracticeCommunicationBoxBase::APracticeCommunicationBoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SenderBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SenderBox"));
	SenderBox->SetupAttachment(RootComponent);
	SenderBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSenderBoxBeginOverlap);

	ReceiverBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ReceiverBox"));
	ReceiverBox->SetupAttachment(RootComponent);
	ReceiverBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnReceiverBoxBeginOverlap);
}

void APracticeCommunicationBoxBase::OnSenderBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APracticeCommunicationBoxBase::OnReceiverBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}





// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PracticeCommunicationBoxBase.generated.h"

class UBoxComponent;

//서로 통신하는 로직의 박스들을 가지는 액터의 베이스

UCLASS()
class PRACTICE_API APracticeCommunicationBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APracticeCommunicationBoxBase();



private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* SenderBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* ReceiverBox;

	
protected:
	UFUNCTION()
	virtual void OnSenderBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnReceiverBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	bool bSended = false;

	UPROPERTY()
	bool bReceived = false;
};

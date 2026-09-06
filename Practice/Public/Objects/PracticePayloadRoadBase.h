// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PracticePayloadRoadBase.generated.h"

class USplineComponent;
//스플라인 컴포넌트를 가지는 액터. Payload를 움직이게 하는 길 역할을 한다.
UCLASS()
class PRACTICE_API APracticePayloadRoadBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APracticePayloadRoadBase();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USplineComponent* GetSplineComponent() const;

protected:
	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	USplineComponent* SplineComponent;
};

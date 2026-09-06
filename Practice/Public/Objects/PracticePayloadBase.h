// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PracticePayloadBase.generated.h"

class UBoxComponent;
//PayLoadGameMode에서 사용될 PayLoad의 Base클래스, 주변에 플레이어 폰이 있어야 움직이며 적이 있을 경우 멈춘다.(오버워치 참고)

UCLASS()
class PRACTICE_API APracticePayloadBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APracticePayloadBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool ShouldStop() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* CollisionBoxComponent;

	//UFUNCTION()
	//virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//virtual void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

private:
	UPROPERTY(VisibleAnywhere) //Stop여부
	bool bShouldStop = false;	

	UPROPERTY(VisibleAnywhere)
	float DeltaInterval = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(1000, 500, 500);
	float PassedTime = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	TArray<APracticeBaseCharacter*> GoodPassengers; //주변에 있는 플레이어 캐릭터
	TArray<APracticeBaseCharacter*> BadPassengers; //주변에 있는 적들

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTargetActor.generated.h"

/*
 * Target에게 다가갈 때 방향을 잡아주는 서비스
 * 
 * void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override
 * : 해당 서비스에서 회전 수행
 * 
 * FBlackboardKeySelector InTargetActorKey
 * : Player블랙보드 키
 */
UCLASS()
class PRACTICE_API UBTService_OrientToTargetActor : public UBTService 
{
	GENERATED_BODY()

	UBTService_OrientToTargetActor();
	//~Begin UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	//~End UBTNode Interface

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category="Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterpSpeed;
	
};

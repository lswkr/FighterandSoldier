// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PracticeAIController.generated.h"

class UAISenseConfig_Sight;
class UAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class PRACTICE_API APracticeAIController : public AAIController
{
	GENERATED_BODY()

public:
	APracticeAIController(const FObjectInitializer& ObjectInitializer);

	//~Begin IGenericTeamAgentInterface Interface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override; //인식된 캐릭터에 대한 태도를 반환하는 함수
	//~End IGenericTeamAgentInterface Interface.

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent; //상대방 인식 Component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;//EnemyPerceptionComponent의 AI퍼셉션에 활용 

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus); //블랙보드의 'TargetActor'키 업데이트, bDetectEnemies=true이므로 Player캐릭터만 감지하여 업데이트 한다.


private:
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnalbleDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta=(EditCondition = "bEnalbleDetourCrowdAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourAvoidanceQuality = 4; //AI품질

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnalbleDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f; //CollisionQuery반경

};

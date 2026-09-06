// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PracticeAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

APracticeAIController::APracticeAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))//AAIController 의 DefaultSubobjectClass중 PathFollowingComponent(경로 이동 컴포넌트)를 UCrowdFollowingComponent 클래스로 설정해준다.
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true; //적만 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 5000.f; //시야 범위
	AISenseConfig_Sight->LoseSightRadius = 0.f; //시야 잃는 범위, 0이므로 0에서 sightRadius까지 다 감지할 수 있다. 
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f; //시야각. 전 방향을 다 볼 수 있다.

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());//UAISenseConfig_Sight를 주Sense로
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1)); //피아식별 아이디. Player캐릭터는 0이다.
}

ETeamAttitude::Type APracticeAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId()) //PlayerCharater의 ID는 0이므로 이 if문이 true면 적으로 설정
	{
		return ETeamAttitude::Hostile;
	}
	
	return ETeamAttitude::Friendly;
}

void APracticeAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnalbleDetourCrowdAvoidance ? ECrowdSimulationState::Enabled: ECrowdSimulationState::Disabled);
	
		switch (DetourAvoidanceQuality)
		{
		case 1:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
		case 2:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
		case 3:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
		case 4:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
		default:
			break;
		}

		CrowdComp->SetAvoidanceGroup(1); //자신이 속한 그룹
		CrowdComp->SetGroupsToAvoid(1);  //피해야할 그룹
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void APracticeAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"),Actor);
			}
		}
	}
}

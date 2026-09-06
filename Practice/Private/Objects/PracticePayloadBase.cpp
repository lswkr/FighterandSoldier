// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/PracticePayloadBase.h"
#include "Components/BoxComponent.h"
#include "Character/PracticeBaseCharacter.h"
#include "Character/PracticeFighterCharacter.h"
#include "Character/PracticeSoldierCharacter.h"
#include "Character/PracticeEnemyCharacter.h"
#include "PracticeFunctionLibrary.h"
#include "PracticeGameplayTags.h"
#include "Kismet/KismetSystemLibrary.h"

#include "PracticeDebugHelper.h"
// Sets default values
APracticePayloadBase::APracticePayloadBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	SetRootComponent(CollisionBoxComponent);
	//CollisionBoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	//CollisionBoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);

	StaticMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APracticePayloadBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APracticePayloadBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PassedTime += DeltaTime;
	
	if (PassedTime >= DeltaInterval) { //Interval마다 주변의 캐릭터들이 있는지 확인하는 연산을 진행
		PassedTime = 0.f;

		TArray<FHitResult> BoxTraceHits;

		UKismetSystemLibrary::BoxTraceMultiForObjects(
			this,
			GetActorLocation(),
			GetActorLocation(),
			TraceBoxSize / 2,
			GetActorRotation(),
			BoxTraceChannel,
			false,
			TArray<AActor*>(),
			bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
			BoxTraceHits,
			true
		);

		for (const FHitResult& HitResult : BoxTraceHits)
		{
			if (APracticeBaseCharacter* Character = Cast<APracticeBaseCharacter>(HitResult.GetActor()))
			{
				if (Character->GetTypeTag() == PracticeGameplayTags::Type_Enemy)
				{
					BadPassengers.AddUnique(Character);
				}
				else if (Character->GetTypeTag() == PracticeGameplayTags::Type_Fighter || Character->GetTypeTag() == PracticeGameplayTags::Type_Soldier)
				{
					GoodPassengers.AddUnique(Character);
				}

			}
		}
	/*	Debug::Print(FString::Printf(TEXT("BadPassengers: %d"), BadPassengers.Num()));
		Debug::Print(FString::Printf(TEXT("GoodPassengers: %d"), GoodPassengers.Num()));*/
		bShouldStop = GoodPassengers.IsEmpty() || !BadPassengers.IsEmpty(); //플레이어 캐릭터가 없거나 Enemy캐릭터가 있으면 Stop

		BadPassengers.Empty(); //체크가 끝났으면 두 배열 모두 비우기
		GoodPassengers.Empty();
		
	}
	

	
}



bool APracticePayloadBase::ShouldStop() const
{
	return bShouldStop;
}


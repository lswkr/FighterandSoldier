// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/PracticeEnemyLoadandSpawnBox.h"
#include "Engine/TargetPoint.h"
#include "Character/PracticeEnemyCharacter.h"
#include "GameModes/PracticePayloadMode.h"
#include "Engine/AssetManager.h"
#include "Character/PracticeFighterCharacter.h"
#include "Character/PracticeSoldierCharacter.h"
#include "PracticeFunctionLibrary.h"
#include "PracticeGameInstance.h"

#include "PracticeDebugHelper.h"

void APracticeEnemyLoadandSpawnBox::PreLoadEnemies()
{
	PreLoadedEnemyClassMap.Empty();

	APracticePayloadMode* PayloadMode = Cast<APracticePayloadMode>(GetWorld()->GetAuthGameMode());
	int32 StageNum =  UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetStageLevel();
	
	for (const FPracticeEnemySpawnerInfo& SpawnerInfo : GetCurrentEnemySpawnerTableRow(StageNum)->EnemySpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo, this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
					}
				}
			)
		);
	}
}

void APracticeEnemyLoadandSpawnBox::TrySpawnEnemies()
{
	checkf(!SpawnActorTargetPoints.IsEmpty(), TEXT("You forgot to assign TargetPoints"));

	int32 EnemiesSpawnedThisTime = SpawnActorTargetPoints.Num();

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	APracticePayloadMode* PayloadMode = Cast<APracticePayloadMode>(GetWorld()->GetAuthGameMode());
	int32 StageNum = UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetStageLevel();
	

	int idx = 0;
	for (const FPracticeEnemySpawnerInfo& SpawnerInfo : GetCurrentEnemySpawnerTableRow(StageNum)->EnemySpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

	//	Debug::Print(SpawnerInfo.SoftEnemyClassToSpawn.GetAssetName());

		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for (const ATargetPoint* Point: SpawnActorTargetPoints)
		{
		//	Debug::Print(Point->GetActorNameOrLabel());
			const FVector SpawnOrigin = Point->GetActorLocation();
			const FRotator SpawnRotation = Point->GetActorForwardVector().ToOrientationRotator();
			
			FVector SpawnLocation = SpawnOrigin + FVector(0.f, 0.f, 150.f);

			APracticeEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<APracticeEnemyCharacter>(LoadedEnemyClass, SpawnLocation, SpawnRotation, SpawnParam);

		}
	}
}

FPracticeEnemySpawnerTableRow* APracticeEnemyLoadandSpawnBox::GetCurrentEnemySpawnerTableRow(int32 StageNum) const
{
	const FName RowName = FName(TEXT("Stage") + FString::FromInt(StageNum)); //TableRow의 이름을 Stage1, Stage2 형식으로 이름을 지음.
//	Debug::Print(RowName.ToString());										 
	FPracticeEnemySpawnerTableRow* FoundRow = EnemySpawnerDataTable->FindRow<FPracticeEnemySpawnerTableRow>(RowName, FString());

	return FoundRow;
}

int32 APracticeEnemyLoadandSpawnBox::GetPointsNum()
{
	return SpawnActorTargetPoints.Num();
}

void APracticeEnemyLoadandSpawnBox::OnSenderBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bSended) //Fighter거나 Soldier가 한 번 Overlap되면 프리로드 시작, 이후 겹쳐지지 않도록 bool변수 사용
	{
		if (Cast<APracticeFighterCharacter>(OtherActor))
		{
			PreLoadEnemies();
			bSended = true;
		}

		else if (Cast<APracticeSoldierCharacter>(OtherActor)) 
		{
			PreLoadEnemies();
			bSended = true;
		}

	}
}

void APracticeEnemyLoadandSpawnBox::OnReceiverBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (!bReceived)//Fighter거나 Soldier가 한 번 Overlap이 끝나면 프리로드 끝난 적을 스폰, 다시 일어나지 않도록 bool변수 사용
	{
		if (Cast<APracticeFighterCharacter>(OtherActor))
		{
			TrySpawnEnemies();
			bReceived = true;
		}

		else if (Cast<APracticeSoldierCharacter>(OtherActor))
		{
			TrySpawnEnemies();
			bReceived = true;
		}

		
	}
}

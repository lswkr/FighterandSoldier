//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "TriggerBox/SpawnEnemiesTriggerBox.h"
//#include "Engine/TargetPoint.h"
//#include "Character/PracticeEnemyCharacter.h"
//#include "Engine/AssetManager.h"
//
//void ASpawnEnemiesTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	if (bHasArrived)
//	{
//		
//		bHasArrived = true;
//	}
//}
//
//void ASpawnEnemiesTriggerBox::BeginPlay()
//{
//	Super::BeginPlay();
//
//}
//
//void ASpawnEnemiesTriggerBox::PreLoadEnemies(int32 StageNum)
//{
//	PreLoadedEnemyClassMap.Empty();
//
//	for (const FPracticeEnemySpawnerInfo2& SpawnerInfo : GetCurrentEnemySpawnerTableRow(StageNum)->EnemySpawnerDefinitions)
//	{
//		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
//
//		UAssetManager::GetStreamableManager().RequestAsyncLoad(
//			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
//			FStreamableDelegate::CreateLambda(
//				[SpawnerInfo, this]()
//				{
//					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
//					{
//						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
//					}
//				}
//			)
//		);
//	}
//}
//
//void ASpawnEnemiesTriggerBox::TrySpawnEnemies(int32 StageNum)
//{
//
//	checkf(!SpawnActorTargetPoints.IsEmpty(), TEXT("You forgot to assign TargetPoints"));
//
//	int32 EnemiesSpawnedThisTime = SpawnActorTargetPoints.Num();
//
//	FActorSpawnParameters SpawnParam;
//	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
//
//	for (const FPracticeEnemySpawnerInfo2& SpawnerInfo : GetCurrentEnemySpawnerTableRow(StageNum)->EnemySpawnerDefinitions)
//	{
//		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
//
//		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);
//
//		for (int32 i = 0; i < EnemiesSpawnedThisTime; i++)
//		{
//			const FVector SpawnOrigin = SpawnActorTargetPoints[i]->GetActorLocation();
//			const FRotator SpawnRotation = SpawnActorTargetPoints[i]->GetActorForwardVector().ToOrientationRotator();
//
//			FVector SpawnLocation = SpawnOrigin + FVector(0.f, 0.f, 150.f);
//
//			APracticeEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<APracticeEnemyCharacter>(SpawnLocation, SpawnRotation, SpawnParam);
//		
//		}
//	}
//}
//
//FPracticeEnemySpawnerTableRow2* ASpawnEnemiesTriggerBox::GetCurrentEnemySpawnerTableRow(int32 StageNum) const
//{
//	const FName RowName = FName(TEXT("Enemies")+FString::FromInt(StageNum));
//
//	FPracticeEnemySpawnerTableRow2* FoundRow = EnemySpawnerDataTable->FindRow<FPracticeEnemySpawnerTableRow2>(RowName, FString());
//
//	return FoundRow;
//}

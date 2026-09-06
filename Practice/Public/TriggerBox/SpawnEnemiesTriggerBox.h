//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "TriggerBox/PracticeTriggerBoxBase.h"
//#include "SpawnEnemiesTriggerBox.generated.h"
///*
//PracticeEnemyLoadandSpawnBox클래스보다 먼저 만들어졌으나 로직이 맞지 않아 보류.
//
//*/
//class ATargetPoint;
//class APracticeEnemyCharacter;
//
//USTRUCT(BlueprintType)
//struct FPracticeEnemySpawnerInfo2
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere)
//	TSoftClassPtr<APracticeEnemyCharacter> SoftEnemyClassToSpawn;
//};
//
//USTRUCT(BlueprintType)
//struct FPracticeEnemySpawnerTableRow2 : public FTableRowBase
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere)
//	TArray<FPracticeEnemySpawnerInfo2> EnemySpawnerDefinitions;
//};
//
//
//UCLASS()
//class PRACTICE_API ASpawnEnemiesTriggerBox : public APracticeTriggerBoxBase
//{
//	GENERATED_BODY()
//	
//public:
//	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
//	TArray<ATargetPoint*> SpawnActorTargetPoints;
//
//protected:
//	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
//	
//	virtual void BeginPlay() override;
//
//private:
//	bool bHasArrived = false;
//
//	void PreLoadEnemies(int32 StageNum);
//	void TrySpawnEnemies(int32 StageNum);
//	FPracticeEnemySpawnerTableRow2* GetCurrentEnemySpawnerTableRow(int32 StageNum) const;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="SpawnDefinition", meta=(AllowPrivateAccess="true"))
//	UDataTable* EnemySpawnerDataTable;
//
//	UPROPERTY()
//	TMap<TSoftClassPtr<APracticeEnemyCharacter>, UClass*> PreLoadedEnemyClassMap;
//
//
//
//};

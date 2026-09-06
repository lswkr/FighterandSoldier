// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/PracticeCommunicationBoxBase.h"
#include "PracticeEnemyLoadandSpawnBox.generated.h"

class ATargetPoint;
class APracticeEnemyCharacter;

USTRUCT(BlueprintType)
struct FPracticeEnemySpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<APracticeEnemyCharacter> SoftEnemyClassToSpawn; //Spawn시킬 Actor의 클래스
};

USTRUCT(BlueprintType)
struct FPracticeEnemySpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FPracticeEnemySpawnerInfo> EnemySpawnerDefinitions; //Spawn시킬 Actor 클래스의 배열
};


/**
 * ReceiverBox를 지나면 Enemy들이 Preload
 * SenderBox를 지나면 Enemy들이 소환된다. 
 */
UCLASS()
class PRACTICE_API APracticeEnemyLoadandSpawnBox : public APracticeCommunicationBoxBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure) //현재 TargetPoints의 개수를 반환
	int32 GetPointsNum();

protected:
	virtual void OnSenderBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnReceiverBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	void PreLoadEnemies();	//비동기 로딩 방식, OnSenderBoxBeginOverlap에서 호출
	void TrySpawnEnemies(); //OnReceiverBoxBeginOverlap에서 호출
	FPracticeEnemySpawnerTableRow* GetCurrentEnemySpawnerTableRow(int32 StageNum) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SpawnDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemySpawnerDataTable;//스폰시킬 Enemy의 종류를 정할 수 있는 데이터 테이블

	UPROPERTY()
	TMap<TSoftClassPtr<APracticeEnemyCharacter>, UClass*> PreLoadedEnemyClassMap; //스폰될 Enemy들의 클래스 Map

	//Enemy들을 Spawn시킬 위치가 되는 TargetPoint들의 배열.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ATargetPoint*> SpawnActorTargetPoints;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/PracticeGameMode.h"
#include "Interfaces/PawnUIInterface.h"
#include "PracticePayloadMode.generated.h"

class APracticeEnemyCharacter;
class APracticePayloadBase;
class APracticePayloadRoadBase;
class ASpawnEnemiesTriggerBox;
class ALocationActor;

UENUM(BlueprintType)
enum class EPracticePayloadGameModeState : uint8
{
	InProgress,
	ArriveStation, //도착. 음악이 멈추고 위젯이 사라진다
	PlayerDied, //음악정지, Pause메뉴
	BossTime, //보스 소환
	BossDied //다음 스테이지로 이동(현재 메뉴 레벨로 이동)
};

USTRUCT(BlueprintType)
struct FPracticeBossBossSpawnerInfo //소환시킬 Boss에 대한 클래스 정보
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<APracticeEnemyCharacter> SoftBossClassToSpawn; 
};

USTRUCT(BlueprintType)
struct FPracticeBossEnemyTableRow : public FTableRowBase //위의 구조체를 가지는 Table
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FPracticeBossBossSpawnerInfo BossEnemySpawnerDefinitions;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPayloadGameModeStateChangedDelegate, EPracticePayloadGameModeState, CurrentState);


UCLASS()
class PRACTICE_API APracticePayloadMode : public APracticeGameMode
{
	GENERATED_BODY()

public:

	APracticePayloadMode();
	//~Begin IGameModeUIInterface Interface
	virtual UGameModeUIComponent* GetGameModeUIComponent() const override;
	virtual UPayloadGameModeUIComponent* GetPayloadGameModeUIComponent() const override;
	//~End IGameModeUIInterface Interface
	//int32 GetGameModeStageNum();
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentPayloadGameModeState(EPracticePayloadGameModeState InState);
	FPracticeBossEnemyTableRow* GetCurrentBossEnemySpawnerTableRow() const;
	void TrySpawnBossEnemy(); //Boss소환
	void PreLoadBoss(); //Boss Preload

	UFUNCTION()
	void OnBossDestroyed(AActor* DestroyedActor);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	APracticePayloadBase* Payload; //사용될 Payload

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	APracticePayloadRoadBase* Road; //Spline컴포넌트를 가지고 있는 액터

	UPROPERTY()
	EPracticePayloadGameModeState CurrentPayloadGameModeState; //현재 게임모드의 상태

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnPayloadGameModeStateChangedDelegate OnPayloadGameModeStateChanged; //게임모드가 바뀔 때마다 브로드캐스트하는 델리게이트

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	int32 TotalStationNum = 1;


	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	float BossWaitingTime = 5.f;//보스의 안정적인 로딩과 긴장감을 위해 기다리는 시간

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	float DistanceAlongSpline = 0.f; //Spline위에서 Payload의 진행 거리

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	float SplineSpeed = 300.f; //Payload의 속도

	UPROPERTY(EditAnywhere, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	AActor* BossTargetPoint;

	//bool bHasArrived = false;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UPayloadGameModeUIComponent* PayloadGameModeUIComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PayloadDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* PracticeBossEnemyTable; //Payload게임모드를 사용하는 스테이지에 따라 소환될 Boss의 정보를 저장해놓은 테이블

	UPROPERTY()
	TMap<TSoftClassPtr<APracticeEnemyCharacter>, UClass*> PreLoadedBossClassMap;

};

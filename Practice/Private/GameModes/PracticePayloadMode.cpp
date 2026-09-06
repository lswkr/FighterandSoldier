// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PracticePayloadMode.h"
#include "Components/UI/PayloadGameModeUIComponent.h"
#include "Objects/PracticePayloadBase.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/PracticePayloadRoadBase.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "Character/PracticeEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Objects/LocationActor.h"
#include "PracticeGameInstance.h"
#include "PracticeFunctionLibrary.h"
#include "PracticeGameInstance.h"

#include "PracticeDebugHelper.h"

APracticePayloadMode::APracticePayloadMode()
{
	PayloadGameModeUIComponent = CreateDefaultSubobject<UPayloadGameModeUIComponent>(TEXT("PayloadGameModeUIComponent")); //Payload가 지나가는 거리를 알려주는 위젯을 사용하기 위해
}

UGameModeUIComponent* APracticePayloadMode::GetGameModeUIComponent() const
{
	return PayloadGameModeUIComponent;
}

UPayloadGameModeUIComponent* APracticePayloadMode::GetPayloadGameModeUIComponent() const
{
	return PayloadGameModeUIComponent;
}


void APracticePayloadMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (UPracticeGameInstance* PracticeGameInstance = GetWorld()->GetGameInstance<UPracticeGameInstance>())
	{
		DefaultPawnClass = PracticeGameInstance->GetPlayerPawn(); //게임인스턴스에서 선택된 캐릭터를 DefaultPawn으로 설정
	}
}

void APracticePayloadMode::BeginPlay()
{
	Super::BeginPlay();
	
	Payload = Cast<APracticePayloadBase>(UGameplayStatics::GetActorOfClass(this, APracticePayloadBase::StaticClass())); //Payload, Road를 레벨에 비치해두고 이를 얻어온다. 
	
	Road = Cast<APracticePayloadRoadBase>(UGameplayStatics::GetActorOfClass(this, APracticePayloadRoadBase::StaticClass()));
	
}

void APracticePayloadMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	checkf(Road, TEXT("You Forgot to assign Road"));
	checkf(Payload,TEXT("You Forgot to assign Payload"));

	//차가 도착하지 않았고, BossTime이 아니고, 화물이 움직일 수 있다면
	if ((CurrentPayloadGameModeState!=EPracticePayloadGameModeState::BossTime && CurrentPayloadGameModeState != EPracticePayloadGameModeState::ArriveStation)&& !Payload->ShouldStop())
	{
		DistanceAlongSpline += SplineSpeed * DeltaTime; //Road의 Spline의 길이 전까지 계속 더해준다.
		FTransform UpdatedTransform = Road->GetSplineComponent()->GetTransformAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World); //변경된 길이만큼의 Spline위에서의 위치.

		Payload->SetActorTransform(UpdatedTransform); //해당 위치로 Payload위치시키기

		PayloadGameModeUIComponent->OnCurrentValueChanged.Broadcast(DistanceAlongSpline / Road->GetSplineComponent()->GetSplineLength()); //위젯에 거리가 잘 나타날 수 있도록 브로드캐스트
		
		if (DistanceAlongSpline>= Road->GetSplineComponent()->GetSplineLength()) //만약 도착하게 된다면
		{
			PreLoadBoss();	//Boss로딩
			TimePassedSinceStart = 0.f; //Boss기다릴 때까지 시간을 세기 위해 0으로 초기화시킴
			SetCurrentPayloadGameModeState(EPracticePayloadGameModeState::ArriveStation); //도착 상태로 게임모드 상태 변경
			
		}

	}
	else if (CurrentPayloadGameModeState == EPracticePayloadGameModeState::ArriveStation) //도착 상태의 경우
	{
		TimePassedSinceStart += DeltaTime; //시간을 세고
		if (TimePassedSinceStart >= BossWaitingTime) //Boss를 다 기다렸으면
		{
			SetCurrentPayloadGameModeState(EPracticePayloadGameModeState::BossTime); //Boss와 싸우는 게임모드로 Set
			TrySpawnBossEnemy();//보스 소환
		}
	}
}

void APracticePayloadMode::SetCurrentPayloadGameModeState(EPracticePayloadGameModeState InState)
{
	CurrentPayloadGameModeState = InState;
	OnPayloadGameModeStateChanged.Broadcast(CurrentPayloadGameModeState); //게임모드 상태가 변경될 때마다 블루프린트에서 브로드캐스팅되어 위젯생성이나 화면 변경과 같은 것을 진행
}

FPracticeBossEnemyTableRow* APracticePayloadMode::GetCurrentBossEnemySpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Stage") + FString::FromInt(UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetStageLevel())); //소환될 Boss에 대한 정보는 Table에서 Stage1 과 같은 이름으로 저장되어있음
	
	FPracticeBossEnemyTableRow* FoundRow = PracticeBossEnemyTable->FindRow<FPracticeBossEnemyTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could Not Find a Valid Row Under The Name %s in the Data Table"), *RowName.ToString());
	
	return FoundRow;
}

void APracticePayloadMode::TrySpawnBossEnemy()
{
	BossTargetPoint = UGameplayStatics::GetActorOfClass(this, ALocationActor::StaticClass()); //TargetPoint 액터는 이미 에너미를 소환할 때 사용하므로 따로 LocationActor란 클래스를 만듬

	checkf(BossTargetPoint, TEXT("No Valid TargetPoint Found in Level"));

	const FPracticeBossBossSpawnerInfo& SpawnerInfo = GetCurrentBossEnemySpawnerTableRow()->BossEnemySpawnerDefinitions;
	
	if (SpawnerInfo.SoftBossClassToSpawn.IsNull())
	{
		return;
	}

	UClass* LoadedBossClass = PreLoadedBossClassMap.FindChecked(SpawnerInfo.SoftBossClassToSpawn); //위의 Row에서 선택한 Boss의 클래스를 설정
	
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector SpawnOrigin = BossTargetPoint->GetActorLocation();
	const FRotator SpawnRotation = BossTargetPoint->GetActorRotation(); //생성위치를 LocationActor의 위치로 설정
	
	APracticeEnemyCharacter* SpawnedBoss = GetWorld()->SpawnActor<APracticeEnemyCharacter>(LoadedBossClass, SpawnOrigin, SpawnRotation, SpawnParam); //소환

	if (SpawnedBoss)
	{
		SpawnedBoss->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnBossDestroyed);//보스가 파괴되었을 때 OnBossDestroyed호출
	}
}

void APracticePayloadMode::PreLoadBoss()
{
	PreLoadedBossClassMap.Empty();
	const FPracticeBossBossSpawnerInfo& SpawnerInfo = GetCurrentBossEnemySpawnerTableRow()->BossEnemySpawnerDefinitions;

	if (SpawnerInfo.SoftBossClassToSpawn.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		SpawnerInfo.SoftBossClassToSpawn.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[SpawnerInfo, this]()
			{
				if (UClass* LoadedBossClass = SpawnerInfo.SoftBossClassToSpawn.Get())
				{
					PreLoadedBossClassMap.Emplace(SpawnerInfo.SoftBossClassToSpawn, LoadedBossClass);
				}
			}
		)
	);
}

void APracticePayloadMode::OnBossDestroyed(AActor* DestroyedActor)	
{
	UPracticeFunctionLibrary::GetPracticeGameInstance(this)->AddStageLevel(1); //StageLevel에 1을 더해준다.
	SetCurrentPayloadGameModeState(EPracticePayloadGameModeState::BossDied);   //BossDied로 상태 변경
}



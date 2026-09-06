// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeGameInstance.h"
#include "Character/PracticeBaseCharacter.h"
#include "MoviePlayer.h"

#include "PracticeDebugHelper.h"
void UPracticeGameInstance::Init()
{
	Super::Init();

	//맵 로딩 전과 후를 알리는 델리게이트들, 로딩 화면 위해 활용
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreloadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);
}

void UPracticeGameInstance::OnPreloadMap(const FString& MapName)   
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.5;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);

}
void UPracticeGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}
TSoftObjectPtr<UWorld> UPracticeGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FPracticeGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}
	return TSoftObjectPtr<UWorld>();
}

TSubclassOf<APawn> UPracticeGameInstance::GetPlayerPawnByTag(FGameplayTag InTag) 
{
	for (const FPracticePawnSet& PlayerPawnSet : PlayerPawnSets)
	{
		if (!PlayerPawnSet.IsValid()) continue;

		if (PlayerPawnSet.PlayerPawnTag == InTag)
		{
			SetPlayerTag(InTag);
			return PlayerPawnSet.PlayerPawn;
		}
	}
	return TSubclassOf<APawn>();
}

void UPracticeGameInstance::SetPlayerPawn(FGameplayTag InTag)
{
	if (TSubclassOf<APawn> PlayerPawnClass = GetPlayerPawnByTag(InTag))
	{
		//Debug::Print(PlayerPawnClass.Get()->GetName());
		PlayerPawn = PlayerPawnClass;
	}
	return;
}

TSubclassOf<APawn> UPracticeGameInstance::GetPlayerPawn()
{
	if (PlayerPawn)
	{
		//Debug::Print(PlayerPawn.Get()->GetName());
		return PlayerPawn;
	}
	return TSubclassOf<APawn>();
}

void UPracticeGameInstance::SetCharacterLevel(int32 Level)
{
	CharacterLevel = Level;
}

int32 UPracticeGameInstance::GetCharacterLevel() const
{
	return CharacterLevel;
}

void UPracticeGameInstance::AddStageLevel(int32 Level)
{
	StageLevel += Level;
}

int32 UPracticeGameInstance::GetStageLevel() const
{
	return StageLevel;
}

void UPracticeGameInstance::SetPlayerTag(FGameplayTag PawnTag)
{
	PlayerPawnTag = PawnTag;
}

FGameplayTag UPracticeGameInstance::GetPlayerTag() const
{
	return PlayerPawnTag;
}

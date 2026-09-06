// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "PracticeGameInstance.generated.h"

class APracticeBaseCharacter;

USTRUCT(BlueprintType)
struct FPracticePawnSet //폰을 식별할 때 태그를 활용하기 위한 구조체
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Pawn"))
	FGameplayTag PlayerPawnTag;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PlayerPawn;

	bool IsValid() const
	{
		return PlayerPawnTag.IsValid() && PlayerPawn;
	}
};

USTRUCT(BlueprintType)
struct FPracticeGameLevelSet //레벨을 식별할 때 태그를 활용하기 위한 구조체
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(Categories="GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};



/**
 * 
 */
UCLASS()
class PRACTICE_API UPracticeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

protected:

	virtual void OnPreloadMap(const FString& MapName); //로딩 스크린 띄우는 함수
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld); //로딩 스크린 끝내는 함수

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FPracticeGameLevelSet> GameLevelSets; //에디터에서 레벨 추가

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPracticePawnSet> PlayerPawnSets; //에디터에서 폰 클래스 추가

public:
	UFUNCTION(BlueprintPure, meta= (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const; //레벨 Getter

	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Pawn"))
	TSubclassOf<APawn> GetPlayerPawnByTag(FGameplayTag InTag);//폰 Getter

	UFUNCTION(BlueprintCallable, meta = (GameplayTagFilter = "GameData.Pawn"))
	void SetPlayerPawn(FGameplayTag InTag); //선택화면에서 캐릭터 선택할 때 사용되는 Setter

	UFUNCTION(BlueprintCallable, meta = (GameplayTagFilter = "GameData.Pawn"))
	TSubclassOf<APawn> GetPlayerPawn(); //게임모드에서 디폴트 폰을 구하는데 활용, 아래 SetPlayerTag 활용 때문에 const함수가 아니다.

	UFUNCTION(BlueprintCallable)
	void SetCharacterLevel(int32 Level); //캐릭터의 레벨 Setter

	UFUNCTION(BlueprintCallable)
	int32 GetCharacterLevel() const; //캐릭터의 레벨 Getter

	UFUNCTION(BlueprintCallable)
	void AddStageLevel(int32 Level); //Stage가 끝나고 다음 스테이지로 넘어갈 때 활용. 지정한 Level만큼 현 레벨에 더한다.
									 //Reset할 경우 현레벨 + -1*(현레벨-1)의 방식으로 활용가능 
	UFUNCTION(BlueprintCallable)
	int32 GetStageLevel() const; //현 스테이지 번호 Getter

	UFUNCTION(BlueprintPure)
	FGameplayTag GetPlayerTag() const; //Pawn 확인할 때 활용되는 태그

	UFUNCTION(BlueprintCallable)
	void SetPlayerTag(FGameplayTag PawnTag); //Pawn의 태그 Setter


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PlayerPawn;//폰의 클래스, 게임모드의 DefaultPawn을 설정하는데 활용

	UPROPERTY()
	int32 StageLevel = 1; //현 스테이지 단계

	UPROPERTY()
	int32 CharacterLevel = 1; //현 캐릭터의 레벨
	
	UPROPERTY()
	FGameplayTag PlayerPawnTag;
};

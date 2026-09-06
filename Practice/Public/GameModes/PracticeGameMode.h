// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/GameModeUIInterface.h"
#include "PracticeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API APracticeGameMode : public AGameModeBase, public IGameModeUIInterface
{
	GENERATED_BODY()
	
public:
	APracticeGameMode();
	
public:
	//~Begin IGameModeUIInterface Interface
	virtual UGameModeUIComponent* GetGameModeUIComponent() const override;
	//~End IGameModeUIInterface Interface
};

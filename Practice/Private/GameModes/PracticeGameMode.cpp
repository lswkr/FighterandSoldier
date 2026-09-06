// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PracticeGameMode.h"

APracticeGameMode::APracticeGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

UGameModeUIComponent* APracticeGameMode::GetGameModeUIComponent() const
{
	return nullptr;
}

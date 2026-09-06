// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PracticePlayerController.h"

APracticePlayerController::APracticePlayerController()
{
    PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId APracticePlayerController::GetGenericTeamId() const
{
    return PlayerTeamID;
}

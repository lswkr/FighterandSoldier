// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UFighterUIComponent* IPawnUIInterface::GetFighterUIComponent() const
{
	return nullptr;
}

USoldierUIComponent* IPawnUIInterface::GetSoldierUIComponent() const
{
	return nullptr;
}

UEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}

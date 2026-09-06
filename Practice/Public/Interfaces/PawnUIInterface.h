// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UPawnUIComponent;
class UFighterUIComponent;
class USoldierUIComponent;
class UEnemyUIComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * AttributSet의 연산을 위젯에 반영시킬 수 있도록 활용하는 인터페이스
 */
class PRACTICE_API IPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPawnUIComponent* GetPawnUIComponent() const =0;
	virtual UFighterUIComponent* GetFighterUIComponent() const;
	virtual	USoldierUIComponent* GetSoldierUIComponent() const;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const;
};

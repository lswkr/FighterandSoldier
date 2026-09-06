// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeUIInterface.generated.h"

class UGameModeUIComponent;
class UPayloadGameModeUIComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Payload의 경우 위의 게임 진행도를 나타내기위해 사용되는 UI 인터페이스
 */
class PRACTICE_API IGameModeUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UGameModeUIComponent* GetGameModeUIComponent() const = 0;
	virtual UPayloadGameModeUIComponent* GetPayloadGameModeUIComponent() const;
};

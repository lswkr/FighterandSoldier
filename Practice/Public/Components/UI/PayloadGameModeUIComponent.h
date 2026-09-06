// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/GameModeUIComponent.h"
#include "PayloadGameModeUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UPayloadGameModeUIComponent : public UGameModeUIComponent
{
	GENERATED_BODY()
	//PayloadGamemode전용 UIComponent로서 UGameModeUIComponent의 OnCurrentValueChanged Delegate를
	//Payload의 거리가 변경될 때에 활용한다.
	
};

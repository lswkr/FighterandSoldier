// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "PracticePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API APracticePlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	APracticePlayerController();

	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface.
	
private:
	FGenericTeamId PlayerTeamID; //Enemy와 Player간의 피아식별을 위한 ID
	
};

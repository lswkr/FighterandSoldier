// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PracticeWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Interfaces/GameModeUIInterface.h"

#include "PracticeDebugHelper.h"

void UPracticeWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (USoldierUIComponent* SoldierUIComponent = PawnUIInterface->GetSoldierUIComponent())//솔저용
		{
			BP_OnOwningSoldierUIComponentInitialized(SoldierUIComponent); 
		}
		else if (UFighterUIComponent* FighterUIComponent = PawnUIInterface->GetFighterUIComponent())//파이터용
		{
			BP_OnOwningFighterUIComponentInitialized(FighterUIComponent); 
		}
	}

	if (IGameModeUIInterface* GameModeUIInterface = Cast<IGameModeUIInterface>(GetWorld()->GetAuthGameMode()))
	{
		if (UPayloadGameModeUIComponent* PayloadGameModeUIComponent = GameModeUIInterface->GetPayloadGameModeUIComponent())
		{
			BP_OnOwningPayloadGameModeUIComponentInitialized(PayloadGameModeUIComponent); //게임모드용
		}
	}
}

void UPracticeWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor) 
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
		
		checkf(EnemyUIComponent,TEXT("Failed to extract an EnemyUIComponent from &s"),*OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent); 
	}
}

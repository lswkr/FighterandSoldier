// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PracticeWidgetBase.generated.h"

class USoldierUIComponent;
class UFighterUIComponent;
class UEnemyUIComponent;
class UGameModeUIComponent;
class UPayloadGameModeUIComponent;

/**
 * 
 */
UCLASS()
class PRACTICE_API UPracticeWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	//위젯블루프린트에서 사용될 이벤트들, 위젯이 초기화 되면서 AttributeSet에서 UI인터페이스를 가지고 브로드캐스트되는 함수들을 바인딩시키도록 NativeOnInitialized에서 활용된다.
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Soldier UI Component Initialized"))
	void BP_OnOwningSoldierUIComponentInitialized(USoldierUIComponent* OwningSoldierUIComponent); 
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Fighter UI Component Initialized"))
	void BP_OnOwningFighterUIComponentInitialized(UFighterUIComponent* OwningFighterUIComponent); 

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Payload GameMode UI Component Initialized"))
	void BP_OnOwningPayloadGameModeUIComponentInitialized(UPayloadGameModeUIComponent* OwningPayloadGameModeUIComponent);
	
public:
	//에너미 캐릭터에게 생길 위젯은 자동으로 initialize되어야 함, APracticeEnemyCharacter의 BeginPlay에서 호출된다.
	//역할은 NativeOnInitialized와 같다.
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

class UPracticeWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntChangedDelegate, int32, NewInt);
/**
 * 
 */
UCLASS()
class PRACTICE_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
public:
	//아래 델리게이트들은 AttributeSet클래스의 PostGameplayEffectExecution함수에서 해당 값들이 변할 때마다 브로드캐스팅을 한다.
	//이를 통해 위젯에 수치 변화를 반영할 수 있다.
	UPROPERTY(BlueprintAssignable) 
	FOnPercentChangedDelegate OnCurrentHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentUltChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentExpChanged;

	UPROPERTY(BlueprintAssignable)
	FOnIntChangedDelegate OnCurrentLevelChanged;

public:
	UFUNCTION(BlueprintCallable) //위젯 생성될 때 위젯들을 등록하는 함수, BossEnemy같은 경우 죽으면 자동으로 위젯을 지울 수 있도록 캐릭터가 생길 때 위젯을 등록한다
	void RegisterDrawnWidget(UPracticeWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable) //특정 상황에 호출되어 그려진 위젯들을 모두 지우는 함수
	void RemoveDrawnWidgetsIfAny();

private:
	TArray<UPracticeWidgetBase*> DrawnWidgets;//그려진 위젯들


};

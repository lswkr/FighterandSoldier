// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameModeUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangedDelegate, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UGameModeUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnValueChangedDelegate OnCurrentValueChanged; //GameMode에서 특정 수치의 추적이 필요할 때 사용하는 델리게이트 
};

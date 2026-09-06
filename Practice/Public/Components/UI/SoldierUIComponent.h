// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "SoldierUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquippedGunChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftGunIcon, int32, Bullets);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGunTriggeredDelegate, int32, Bullets);


/**
 * 
 */
UCLASS()
class PRACTICE_API USoldierUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable) //총이 바뀔 때 호출(GunItem을 Consume하거나 해당 Gun의 총알을 다 썼을 경우)
	FOnEquippedGunChangedDelegate OnEquippedGunChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable) //총을 쏠 때 호출(Bullet의 값을 반영)
	FOnGunTriggeredDelegate OnGunTriggered;
};

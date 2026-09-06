// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PracticeBaseAnimInstance.h"
#include "PracticeSoldierLinkedAnimLayer.generated.h"

class UPracticeSoldierAnimInstance;
/*
 * 궁극기 사용 시 다른 블렌드 스페이스를 사용하기 위해 만들었으나 
 * 궁극기에 활용될 걷는 애니메이션이 없어 구현 중단
 */
UCLASS()
class PRACTICE_API UPracticeSoldierLinkedAnimLayer : public UPracticeBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UPracticeSoldierAnimInstance* GetSoldierAnimInstance() const;
	
};

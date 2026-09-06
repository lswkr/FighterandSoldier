// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPracticeInputActionConfig //인풋 태그와 그에 해당하는 인풋 액션을 연결시킨 구조체
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const {
		return InputTag.IsValid() && InputAction;
	}
};

/**
 * 인풋액션과 어빌리티/함수를 태그로 연결시키기 위한 DataAsset
 */
UCLASS()
class PRACTICE_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext; //기본적으로 사용되는 매핑 컨텍스트, Player캐릭터의 SetupPlayerInputComponent에서 매핑컨텍스트로 설정된다.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag")) 
	TArray<FPracticeInputActionConfig> NativeInputActions; //C++파일에 호출될 로직이 있는 것들용

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;//태그에 맞는 인풋액션을 config배열에서 찾아줌 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPracticeInputActionConfig> AbilityInputActions; //어빌리티용
};

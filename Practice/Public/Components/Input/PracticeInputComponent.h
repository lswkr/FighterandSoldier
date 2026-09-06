// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "PracticeInputComponent.generated.h"

/**
 * SetupPlayerInputComponent에서 PlayerInputComponent를 이 클래스로 캐스팅하여
 * 아래 함수들을 이용해 BindAction함수를 통해 Binding시킨다. 
 */
UCLASS()
class PRACTICE_API UPracticeInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc> //C++에서 구현한 액션들을 바인딩 시키는 함수, 캐릭터의 DataAsset_InputConfig에 있는 것들을 활용한다.
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
	template<class UserObject, typename CallbackFunc> //어빌리티를 바인딩 시키는 함수
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
	
};

template<class UserObject, typename CallbackFunc>
inline void UPracticeInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input Config Data Asset is Null, can not proceed with binding"));
	
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UPracticeInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input Config Data Asset is Null, can not proceed with binding"));

	for (const FPracticeInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;
		
		//ETriggerEvent::Started는 눌렸을 때, ETriggerEvent::Completed는 땠을 때다. 각각 Pressed, Released콜백 함수를 바인딩한다.
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag); //이렇게 어빌리티마다 고유한 인풋 태그로 하나의 콜백 함수로 여러 바인딩이 가능해진다.
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}

}

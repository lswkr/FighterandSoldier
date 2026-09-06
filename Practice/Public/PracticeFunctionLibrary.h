// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "PracticeTypes/PracticeEnumTypes.h"
#include "PracticeFunctionLibrary.generated.h"

class UPracticeAbilitySystemComponent;
class UPawnCombatComponent;
struct FScalableFloat;
class UPracticeGameInstance;

/**
 * 
 */

UCLASS()
class PRACTICE_API UPracticeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//주석 없는 함수의 기능은 이름 참고, Native붙은 것들은 C++전용, BP_붙은 것들은 BP에서만 사용, 그 이 외에는 C++, BP양쪽 사용 가능
	static UPracticeAbilitySystemComponent* NativeGetPracticeASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Practice|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd); 

	UFUNCTION(BlueprintCallable, Category = "Practice|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove); 

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Practice|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EPracticeConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Practice|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EPracticeValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Practice|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn); //피아식별 함수

	UFUNCTION(BlueprintCallable, Category = "Practice|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintPure, Category="Practice|FunctionLibrary",meta=(CompactNodeTitle="Get Value At Level")) // 레벨마다 다른 수치를 얻는 로직 상 필요한 함수
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category="Practice|FunctionLibrary") //맞았을 때 나와 적의 위치에 따라 다른 방향으로의 애니메이션을 지정하기 위한 함수 
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Practice|FunctionLibrary", meta = (WorldContext= "WorldContextObject"))
	static UPracticeGameInstance* GetPracticeGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Practice|FunctionLibrary", meta = (WorldContext = "WorldContextObject")) //정지 버튼을 누르거나 죽었을 때 InputMode를 바꾸는 함수
	static void ToggleInputMode(const UObject* WorldContextObject, EPracticeInputMode InInputMode);

};

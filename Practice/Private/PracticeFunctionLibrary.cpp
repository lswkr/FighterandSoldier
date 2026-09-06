// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "PracticeGameplayTags.h"
#include "PracticeGameInstance.h"

#include "PracticeDebugHelper.h"

UPracticeAbilitySystemComponent* UPracticeFunctionLibrary::NativeGetPracticeASCFromActor(AActor* InActor)
{
	check(InActor); 
	return CastChecked<UPracticeAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UPracticeAbilitySystemComponent* ASC = NativeGetPracticeASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UPracticeFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UPracticeAbilitySystemComponent* ASC = NativeGetPracticeASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UPracticeFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UPracticeAbilitySystemComponent* ASC = NativeGetPracticeASCFromActor(InActor);
	
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UPracticeFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EPracticeConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck)? EPracticeConfirmType::Yes : EPracticeConfirmType::No;
}

UPawnCombatComponent* UPracticeFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetUPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UPracticeFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EPracticeValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EPracticeValidType::Valid : EPracticeValidType::InValid;
	return CombatComponent;
}

bool UPracticeFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

bool UPracticeFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UPracticeAbilitySystemComponent* SourceASC = NativeGetPracticeASCFromActor(InInstigator);
	UPracticeAbilitySystemComponent* TargetASC = NativeGetPracticeASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

float UPracticeFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UPracticeFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormarlized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	//내적으로 양 액터 간의 각도 차를 알아낸다.
	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormarlized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormarlized);
	//외적 결과의 Z값으로 오른쪽, 왼쪽 구별
	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1;
	}

	if (OutAngleDifference >= -45 && OutAngleDifference <= 45)
	{
		return PracticeGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45 && OutAngleDifference >= -135)
	{
		return PracticeGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135 || OutAngleDifference > 135)
	{
		return PracticeGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45 && OutAngleDifference <= 135)
	{
		return PracticeGameplayTags::Shared_Status_HitReact_Right;
	}
	return PracticeGameplayTags::Shared_Status_HitReact_Front;
}

UPracticeGameInstance* UPracticeFunctionLibrary::GetPracticeGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UPracticeGameInstance>(); 
		}

	}

	return nullptr;
}

void UPracticeFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EPracticeInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}
	if (!PlayerController)
	{
		return;
	}
	
	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnlyMode;

	switch (InInputMode)
	{
	case EPracticeInputMode::GameOnly:	//게임 중일 땐
		
		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->bShowMouseCursor = false;	//마우스 안 보이게
		
		break;

	case EPracticeInputMode::UIOnly: //메뉴화면 등

		PlayerController->SetInputMode(UIOnlyMode);
		PlayerController->bShowMouseCursor = true;	//마우스 보이게

		break;

	default:

		break;
	}
}

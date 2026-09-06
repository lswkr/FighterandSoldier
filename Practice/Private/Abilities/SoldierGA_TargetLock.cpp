// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SoldierGA_TargetLock.h"
#include "Widgets/PracticeWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/PracticeSoldierCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controller/PracticePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Widgets/PracticeWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystem/PracticeAttributeSet.h"
#include "Character/PracticeBaseCharacter.h"
#include "PracticeFunctionLibrary.h"
#include "Character/PracticeEnemyCharacter.h"

#include "PracticeDebugHelper.h"

void USoldierGA_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	InitTargetLockMovement();
	InitTargetLockMappingContext();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USoldierGA_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();

	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USoldierGA_TargetLock::OnTargetLockTick(float DeltaTime)
{
	CurrentTime += DeltaTime;
	TimePassed += DeltaTime;

	TargetLockWidgetSize.X = UKismetMathLibrary::Max(FinalTargetLockWidgetSize.X, TargetLockWidgetSize.X - DeltaInterval); //서서히 줄어들되 최종위젯 사이즈까지는 안 줄도록
	TargetLockWidgetSize.Y = UKismetMathLibrary::Max(FinalTargetLockWidgetSize.Y, TargetLockWidgetSize.Y - DeltaInterval);

	if (CurrentTime >= DeltaInterval) {
		CurrentTime = 0;
		GetAvailableActorsToLock();
		TryLockOnTarget();
	} 
}

void USoldierGA_TargetLock::TryLockOnTarget()
{
	
	/*if (AvailableActorsToLock.IsEmpty())
	{
		//타겟될 액터들이 없으면 바로 취소: 추후 필요시 사용
		CancelTargetLockAbility();
		return;
	}*/

	for (UUserWidget* DrawnTargetLockWidget : DrawnTargetLockWidgets) //위젯 그리기 전 이전 Interval에 그려진 위젯 제거
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidgets.Empty();//그려진 위젯 삭제

	for (const AActor* CurrentLockedActor : AvailableActorsToLock)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in blueprint"));

		UPracticeWidgetBase* DrawnTargetLockWidget = nullptr;
		if (const APracticeEnemyCharacter* EnemyCharacter = Cast<APracticeEnemyCharacter>(CurrentLockedActor))
		{
			FVector2D ScreenPosition; //화면에 띄울 위젯 위치
			if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
				GetPlayerControllerFromActorInfo(),
				CurrentLockedActor->GetActorLocation(),
				ScreenPosition,
				true
			))
			{
				
				if (TimePassed < FinishTime) //시간 다 채우기 전 원 위젯
				{
					DrawnTargetLockWidget = CreateWidget<UPracticeWidgetBase>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);
				}
				else //시간 다 채웠으면 해골 위젯
				{
					DrawnTargetLockWidget = CreateWidget<UPracticeWidgetBase>(GetPlayerControllerFromActorInfo(), TargetDeathWidgetClass);
				}

				check(DrawnTargetLockWidget);

				DrawnTargetLockWidget->AddToViewport();
				float X = UKismetMathLibrary::Max((FinishTime / TimePassed) * TargetLockWidgetSize.X, TargetLockWidgetSize.X);
				float Y = UKismetMathLibrary::Max((FinishTime / TimePassed) * TargetLockWidgetSize.Y, TargetLockWidgetSize.Y);
				DrawnTargetLockWidget->WidgetTree->ForEachWidget(

					[this,X,Y](UWidget* FoundWidget)
					{
						if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
						{
							FoundSizeBox->SetWidthOverride(X);
							FoundSizeBox->SetHeightOverride(Y);
						}
					}
				);
				
				ScreenPosition -= (FVector2D(X,Y) / 2.f);
				DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
				/* DrawnTargetLockWidgets: 그려진 위젯들 다 지우기 위해 저장하는 배열 */
				DrawnTargetLockWidgets.AddUnique(DrawnTargetLockWidget); 
			}
		}


	}
}


TArray<AActor*> USoldierGA_TargetLock::GetAvailableActorsToLock()
{	
	AvailableActorsToLock.Empty();
	
	TArray<FHitResult> BoxTraceHits;
	FRotator TargettingRotation;
	FVector TargettingLocation;
	
	//정면에 박스 생성, 후면은 Targgetting할 수 없다.
	GetPlayerControllerFromActorInfo()->GetPlayerViewPoint(TargettingLocation,TargettingRotation);

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetSoldierCharacterFromActorInfo(),
		TargettingLocation + TargettingRotation.Vector() * TraceBoxSize.X,
		TargettingLocation + TargettingRotation.Vector() * TraceBoxSize.X,
		TraceBoxSize,
		GetPlayerControllerFromActorInfo()->GetDesiredRotation(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	
	for (const FHitResult& TraceHit : BoxTraceHits) //타겟팅 되었을 때 오브젝트 뒤에 있는 적들은 피할 수 있도록 라인트레이스로 한 번 더 검사
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (APawn* HitPawn = Cast<APawn>(TraceHit.GetActor())) 
			{
				FHitResult LineTraceHit;
				
				if (UKismetSystemLibrary::LineTraceSingleForObjects(
					GetSoldierCharacterFromActorInfo(),
					GetSoldierCharacterFromActorInfo()->GetActorLocation(),
					HitPawn->GetActorLocation(),
					LineTraceChannel,
					false,
					TArray<AActor*>(),
					bShowPersistentDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
					LineTraceHit,
					true
				))
				{
					continue;
				}
				if (UPracticeFunctionLibrary::IsTargetPawnHostile(HitPawn, GetSoldierCharacterFromActorInfo()))
				{
					AvailableActorsToLock.AddUnique(HitActor);
				}
			}
		}
	}
	return AvailableActorsToLock;
}




void USoldierGA_TargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetSoldierCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;

	GetSoldierCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void USoldierGA_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}
//
//void USoldierGA_TargetLock::CancelTargetLockAbility()
//{
//	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
//}

void USoldierGA_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	for (UUserWidget* DrawnTargetLockWidget : DrawnTargetLockWidgets)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidgets.Empty();
	
	CachedDefaultMaxWalkSpeed = 0.f;

}

void USoldierGA_TargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetSoldierCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void USoldierGA_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);
	Subsystem->RemoveMappingContext(TargetLockMappingContext);

}

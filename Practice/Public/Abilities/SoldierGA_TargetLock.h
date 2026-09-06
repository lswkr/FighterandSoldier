// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PracticeSoldierGameplayAbility.h"
#include "SoldierGA_TargetLock.generated.h"

class UInputMappingContext;
class UPracticeWidgetBase;

/*
 *	void OnTargetLockTick(float DeltaTime)
 *	: ExecuteTaskOnTick을 통해 Tick마다 호출되는 함수, 데미지의 대상이 되는 적들을 찾는다.
 *
 *	TArray<AActor*> GetAvailableActorsToLock()
 *	:공격 대상이 되는 액터들 반환
 *
 *	void TryLockOnTarget()
 *	:OnTargetLockTick에서 Target을 모으는 함수
 *	
 *	void InitTargetLockMovement()
 *	: 궁극기 사용 시, 움직임을 느리게 설정하기 위한 함수
 *	
 *	void InitTargetLockMappingContext()
 *	: 궁극기 사용 시, Targetting 중 Fire키를 기본 공격키로 하는 매핑컨텍스트로 덮어쓰는 함수
 *
 *	void CancelTargetLockAbility()
 *	: 궁극기가 취소됐을 때 활용되는 함수. 현재 구현시킨 궁극기에선 쓸 일 없어 주석처리. 필요 시 사용 
 *	void CleanUp()
 *	: 흔적 지우기 위한 함수. EndAbility에서 활용된다.
 *	void ResetTargetLockMovement()
 *	: 움직임을 원래대로 되돌리기 위한 함수
 *	void ResetTargetLockMappingContext()
 *	: 매핑 컨텍스트를 원래대로 되돌리기 위한 함수
 *	
 *	bool bShowPersistentDebugShape
 *	: 디버깅 용 부울 변수
 *	
 *	float DeltaInterval
 *	: 호출 주기 조절 변수
 *	
 *	float CurrentTime
 *	: OnTargetLockTick에서 시간을 세기 위해 사용하는 변수, Interval마다 0으로 초기화
 *	float TimePassed
 *	: 블루프린트에서 활용. 궁극기 시작부터 계속 시간을 세는 변수. CurrentTime과 달리 초기화 되지 않는다.
 *	
 *	TSubclassOf<UPracticeWidgetBase> TargetLockWidgetClass
 *	: 타겟팅 되는 중의 붉은 원 위젯
 *	TSubclassOf<UPracticeWidgetBase> TargetDeathWidgetClass
 *	: 최대 데미지가 되었을 때의 해골 위젯
 *	
 *	FVector2D FinalTargetLockWidgetSize 
 *	: 감소될 때 최종 위젯 사이즈
 *
 *	float FinishTime
 *	:궁극기의 최종 데미지에 도달하는데 걸리는 시간
 */

UCLASS()
class PRACTICE_API USoldierGA_TargetLock : public UPracticeSoldierGameplayAbility
{
	GENERATED_BODY()
	
public:


protected:
	//~Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	//~End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetAvailableActorsToLock();

private:
	void TryLockOnTarget();
	
	void InitTargetLockMovement(); 
	void InitTargetLockMappingContext(); 

//	void CancelTargetLockAbility();
	void CleanUp();
	void ResetTargetLockMovement(); 
	void ResetTargetLockMappingContext();


	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	float BoxTraceDistance = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	FVector TraceBoxSize = FVector(3000.f,3000.f,200.f); 

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel; 
	
	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery>> LineTraceChannel; 

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	bool bShowPersistentDebugShape = false; 

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float DeltaInterval = 0.1f; 

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float CurrentTime = 0.f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TargetLock", meta = (AllowPrivateAccess = "true"))
	float TimePassed = 0.f; 

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TSubclassOf<UPracticeWidgetBase> TargetLockWidgetClass; 

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock") 
	TSubclassOf<UPracticeWidgetBase> TargetDeathWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float TargetLockMaxWalkSpeed = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	FVector2D FinalTargetLockWidgetSize = FVector2D(50.f, 50.f); 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TargetLock", meta = (AllowPrivateAccess = "true"))
	float FinishTime = 5.f; 
	
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	TArray<UPracticeWidgetBase*> DrawnTargetLockWidgets;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;

};

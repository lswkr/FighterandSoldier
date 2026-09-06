// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PracticeBaseCharacter.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "AbilitySystem/PracticeAttributeSet.h"
#include "Components/BoxComponent.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"

#include "PracticeDebugHelper.h"

APracticeBaseCharacter::APracticeBaseCharacter()
{
PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	GetMesh()->bReceivesDecals = false;

	PracticeAbilitySystemComponent = CreateDefaultSubobject<UPracticeAbilitySystemComponent>(TEXT("PracticeAbilitySystemComponent"));

	PracticeAttributeSet = CreateDefaultSubobject<UPracticeAttributeSet>(TEXT("PracticeAttributeSet"));

	LeftCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftCollisionBox"));
	LeftCollisionBox->SetupAttachment(GetMesh());
	LeftCollisionBox->SetBoxExtent(FVector(20.f));
	LeftCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	LeftCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxEndOverlap);

	RightCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightCollisionBox"));
	RightCollisionBox->SetupAttachment(GetMesh());
	RightCollisionBox->SetBoxExtent(FVector(20.f));
	RightCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	RightCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxEndOverlap);

	FootCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FootCollisionBox"));
	FootCollisionBox->SetupAttachment(GetMesh());
	FootCollisionBox->SetBoxExtent(FVector(20.f));
	FootCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FootCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	FootCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxEndOverlap);

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* APracticeBaseCharacter::GetAbilitySystemComponent() const
{
	return GetPracticeAbilitySystemComponent();
}

UPawnCombatComponent* APracticeBaseCharacter::GetUPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* APracticeBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void APracticeBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (PracticeAbilitySystemComponent)
	{
		PracticeAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
void APracticeBaseCharacter::Tick(float DeltaTime)
{
	//콜리전 글리치 방지 위해
	FHitResult HitResult;
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(1.0f, 1.0f, 0.0f), GetActorRotation(),true, HitResult,ETeleportType::None);
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(-1.0f, -1.0f, 0.0f), GetActorRotation(),true, HitResult,ETeleportType::None);
	 	
}
void APracticeBaseCharacter::ApplyEffectLevelUp(int32 NewLevel)
{

}
#if WITH_EDITOR
void APracticeBaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftCollisionBoxAttachBoneName))
	{
		LeftCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightCollisionBoxAttachBoneName))
	{
		RightCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, FootCollisionBoxAttachBoneName))
	{
		FootCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FootCollisionBoxAttachBoneName);
	}
}
#endif

void APracticeBaseCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APracticeBaseCharacter::OnBodyCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}




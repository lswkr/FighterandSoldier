// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PracticeFighterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/PracticeInputComponent.h"
#include "PracticeGameplayTags.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "DataAssets/StartUpData/DataAsset_FighterStartUpData.h"
#include "Components/Combat/FighterCombatComponent.h"
#include "Components/UI/FighterUIComponent.h"
#include "PracticeFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PracticeGameInstance.h"

#include "PracticeDebugHelper.h"

APracticeFighterCharacter::APracticeFighterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector(0.f, 55.f, 65.f);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; //¸¶Âû·Â, °ª ³ôÀ» ¼ö·Ï ¾È ¹Ì²ô·¯Áü

	FighterCombatComponent = CreateDefaultSubobject<UFighterCombatComponent>(TEXT("FighterCombatComponent"));
	
	FighterUIComponent = CreateDefaultSubobject<UFighterUIComponent>(TEXT("FighterUIComponent"));

	TypeTag = PracticeGameplayTags::Type_Fighter;
}

UPawnCombatComponent* APracticeFighterCharacter::GetUPawnCombatComponent() const
{
	return FighterCombatComponent;
}

UPawnUIComponent* APracticeFighterCharacter::GetPawnUIComponent() const
{
	return FighterUIComponent;
}

UFighterUIComponent* APracticeFighterCharacter::GetFighterUIComponent() const
{
	return FighterUIComponent;
}

void APracticeFighterCharacter::ApplyEffectLevelUp(int32 NewLevel)
{
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->OnLevelUp(PracticeAbilitySystemComponent, NewLevel);
		}
	}
}

void APracticeFighterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(PracticeAbilitySystemComponent, UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetCharacterLevel());
		}
		FighterUIComponent->OnCurrentLevelChanged.Broadcast(UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetCharacterLevel());
	}

}

void APracticeFighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input Config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UPracticeInputComponent* PracticeInputComponent = CastChecked<UPracticeInputComponent>(PlayerInputComponent);

	PracticeInputComponent->BindNativeInputAction(InputConfigDataAsset, PracticeGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	PracticeInputComponent->BindNativeInputAction(InputConfigDataAsset, PracticeGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	PracticeInputComponent->BindNativeInputAction(InputConfigDataAsset, PracticeGameplayTags::InputTag_PickUp, ETriggerEvent::Started, this, &ThisClass::Input_PickUpItemsStarted);

	PracticeInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void APracticeFighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APracticeFighterCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UPracticeFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			FighterCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void APracticeFighterCharacter::OnBodyCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor)) {
		if (UPracticeFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			FighterCombatComponent->OnHitBoxPulledFromTargetActor(HitPawn);
		}
	}
	
}

void APracticeFighterCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APracticeFighterCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//
//void APracticeFighterCharacter::Input_Jump(const FInputActionValue& InputActionValue) 
//{
//	ACharacter::Jump();	
//}

void APracticeFighterCharacter::Input_PickUpItemsStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		PracticeGameplayTags::Player_Shared_Event_Consume,
		Data
	);
}

void APracticeFighterCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	PracticeAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void APracticeFighterCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	PracticeAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

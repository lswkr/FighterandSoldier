// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PracticeSoldierCharacter.h"
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
#include "Components/Combat/SoldierCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/UI/SoldierUIComponent.h"
#include "PracticeFunctionLibrary.h"
#include "PracticeGameInstance.h"

#include "PracticeDebugHelper.h"


APracticeSoldierCharacter::APracticeSoldierCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = true;
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
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GunCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GunCollisionBox"));
	GunCollisionBox->SetupAttachment(GetMesh(),TEXT("GunMeleeSocket"));
	GunCollisionBox->SetBoxExtent(FVector(20.f));
	GunCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GunCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	GunCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxEndOverlap);

	SoldierCombatComponent = CreateDefaultSubobject<USoldierCombatComponent>(TEXT("SoldierCombatComponent"));

	SoldierUIComponent = CreateDefaultSubobject<USoldierUIComponent>(TEXT("SoldierUIComponent"));

	TypeTag = PracticeGameplayTags::Type_Soldier;
}

UPawnCombatComponent* APracticeSoldierCharacter::GetUPawnCombatComponent() const
{
	return SoldierCombatComponent;
}

UPawnUIComponent* APracticeSoldierCharacter::GetPawnUIComponent() const
{
	return SoldierUIComponent;
}

USoldierUIComponent* APracticeSoldierCharacter::GetSoldierUIComponent() const
{
	return SoldierUIComponent;
}

void APracticeSoldierCharacter::ApplyEffectLevelUp(int32 NewLevel)
{
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->OnLevelUp(PracticeAbilitySystemComponent, NewLevel);
		}
	}
}

void APracticeSoldierCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(PracticeAbilitySystemComponent, UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetCharacterLevel());
		}
		SoldierUIComponent->OnCurrentLevelChanged.Broadcast(UPracticeFunctionLibrary::GetPracticeGameInstance(this)->GetCharacterLevel());
	}
}

void APracticeSoldierCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void APracticeSoldierCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);//Soldier캐릭터의 스켈레탈메시 원본에서 저 위치에 총이 있음.이를 숨겼다.
	
	UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(this, PracticeGameplayTags::Player_Soldier_Status_BulletsEmpty);	//Default Gun은 이 태그가 있어야 작동하므로 시작할 때 이 태그를 부여
	SoldierUIComponent->OnGunTriggered.Broadcast(0); //처음에는 총알이 0이므로 위젯에 0을 준다
}

void APracticeSoldierCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UPracticeFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			SoldierCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void APracticeSoldierCharacter::OnBodyCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor)) 
	{
		if (UPracticeFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			SoldierCombatComponent->OnHitBoxPulledFromTargetActor(HitPawn);
		}
	}

}

void APracticeSoldierCharacter::Input_Move(const FInputActionValue& InputActionValue)
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

void APracticeSoldierCharacter::Input_Look(const FInputActionValue& InputActionValue)
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

//void APracticeSoldierCharacter::Input_Jump(const FInputActionValue& InputActionValue)
//{
//	ACharacter::Jump();
//}

void APracticeSoldierCharacter::Input_PickUpItemsStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		PracticeGameplayTags::Player_Shared_Event_Consume,
		Data
	);
}

void APracticeSoldierCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	PracticeAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void APracticeSoldierCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	PracticeAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

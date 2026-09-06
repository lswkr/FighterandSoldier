// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PracticeEnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "Components/UI/EnemyUIComponent.h"
#include "PracticeFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "Widgets/PracticeWidgetBase.h"
#include "PracticeGameplayTags.h"

#include "PracticeDebugHelper.h"

APracticeEnemyCharacter::APracticeEnemyCharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

    EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

    EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
    EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
    EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

    TypeTag = PracticeGameplayTags::Type_Enemy;
}

UPawnCombatComponent* APracticeEnemyCharacter::GetUPawnCombatComponent() const
{
    return EnemyCombatComponent;
}

UPawnUIComponent* APracticeEnemyCharacter::GetPawnUIComponent() const
{
    return EnemyUIComponent;
}

UEnemyUIComponent* APracticeEnemyCharacter::GetEnemyUIComponent() const
{
    return EnemyUIComponent;
}

void APracticeEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (UPracticeWidgetBase* HealthWidget = Cast<UPracticeWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
    {
        HealthWidget->InitEnemyCreatedWidget(this); 
    }
}

void APracticeEnemyCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    InitEnemyStartUpData();
}

void APracticeEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (APawn* HitPawn = Cast<APawn>(OtherActor))
    {
        if (UPracticeFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
        {
            EnemyCombatComponent->OnHitTargetActor(HitPawn);
        }
    }
}

void APracticeEnemyCharacter::InitEnemyStartUpData()
{
    if (CharacterStartUpData.IsNull())
    {
        return;
    }

    int32 AbilityApplyLevel = 1;

    UAssetManager::GetStreamableManager().RequestAsyncLoad( 
        CharacterStartUpData.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda(
            [this, AbilityApplyLevel]()
            {
                if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get()) 
                {
                    LoadedData->GiveToAbilitySystemComponent(PracticeAbilitySystemComponent, AbilityApplyLevel);
                }
            }
        )
    );
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PracticeProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PracticeFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PracticeGameplayTags.h"
#include "PracticeFunctionLibrary.h"

#include "PracticeDebugHelper.h"

APracticeProjectileBase::APracticeProjectileBase()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	ProjectileStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileStaticMeshComponent")); 
	ProjectileStaticMeshComponent->SetupAttachment(GetRootComponent());

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1200.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}


void APracticeProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap) 
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void APracticeProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn) //Pawn으로 캐스팅 되지 않는다면 파괴
	{
		Destroy();
		return;
	}
	else if (!UPracticeFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn)) //아군 또는 자기자신이면 닿았을 때 아무 영향없이 사라짐
	{
		Destroy();
		return;
	}

	if (UPracticeFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn)) {
		if (ProjectileType != EProjectileType::Explode)
		{
			FGameplayEventData Data;
			Data.Instigator = this;
			Data.Target = HitPawn;
			HandleApplyProjectileDamage(HitPawn, Data);
			BP_OnProjectileHit(HitPawn);
		}
		else
		{	
			BP_OnProjectileHit(HitPawn); //Hit의 경우 맞았을 때 바로 데미지를 줄 수 있지만 
										//Explode의 경우 주변에도 다 데미지를 줘야하므로 따로 함수 호출만 하고
										//남은 연산은 블루프린트에서 한다.
		}
		Destroy();
	}
	
}

void APracticeProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor)) 
	{
		return;
	}
	
	OverlappedActors.AddUnique(OtherActor);

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		FGameplayEventData Data;
		Data.Instigator = this;
		Data.Target = HitPawn;
		if (UPracticeFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
		{
			HandleApplyProjectileDamage(HitPawn, Data);
		}
		
	}
}

void APracticeProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());
	
	const bool bWasApplied = UPracticeFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageSpecHandle);

	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			PracticeGameplayTags::Shared_Event_HitReact,
			InPayload
		);
	}

}

void APracticeProjectileBase::HandleApplyProjectileExp()
{
	checkf(ProjectileExpSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());
	
	UPracticeFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), GetInstigator(), ProjectileExpSpecHandle);

}


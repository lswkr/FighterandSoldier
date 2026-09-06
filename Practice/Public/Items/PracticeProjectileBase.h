// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "PracticeProjectileBase.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;
struct FGameplayEventData;

UENUM(BlueprintType)
enum class EProjectileDamagePolicy :uint8
{
	OnHit,// Hit됐을 때에만 데미지 주는 방식
	OnBeginOverlap, // Overlap되어 여러 캐릭터에 데미지 주는 방식
};

UENUM(BlueprintType)
enum class EProjectileType :uint8
{
	Hit, 
	Overlap,
	Explode //OnHit면서 Explode인 Projectile의 경우 닿으면 폭발하며 주변의 적들에게 스플래시데미지를 준다
};


UCLASS()
class PRACTICE_API APracticeProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APracticeProjectileBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UBoxComponent* ProjectileCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* ProjectileStaticMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* ProjectileNiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	EProjectileDamagePolicy ProjectileDamagePolicy = EProjectileDamagePolicy::OnHit; //기본적으로 OnHit. 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	EProjectileType ProjectileType = EProjectileType::Hit;

	//아래 두 개의 이펙트스펙핸들은 Projectile타입의 총에서 Projectile을 SpawnActor할 때 MakeExpSpecHandle과 MakeDamageSpecHandle을 연결시킨다.
	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle ProjectileDamageSpecHandle;
	
	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle ProjectileExpSpecHandle;
	//UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	//FGameplayEffectSpecHandle ProjectileUltSpecHandle;

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);  
	
	//Overlap타입의 Projectile이 여러 캐릭터를 통과시킬 때 사용되는 함수, 2025/04/20현재 해당 되는 Projectile없음
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Projectile Hit"))
	void BP_OnProjectileHit(APawn* InHitPawn);//닿았을 때 또 데미지 전달 뿐만 아니라 다른 연산을 블루프린트에서 할 수 있도록

	UFUNCTION(BlueprintCallable,Category="Projectile")
	void HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void HandleApplyProjectileExp();

private:
	TArray<AActor*> OverlappedActors;
};

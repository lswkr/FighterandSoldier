// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PracticeTypes/PracticeStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "PracticeGunBase.generated.h"

UENUM(BlueprintType)
enum class EGunType : uint8
{
	LineTrace,
	Projectile

};

UCLASS()
class PRACTICE_API APracticeGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APracticeGunBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GunData")
	FPracticeGunData GunData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles); //총을 장착시킬 때 총의 어빌리티 스펙핸들을 여기서 할당한다.

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* GunMesh;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles; //총이 가지고 있는 이빌리티의 스펙핸들

	
};

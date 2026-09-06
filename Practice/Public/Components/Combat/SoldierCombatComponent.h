// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "SoldierCombatComponent.generated.h"

struct FPracticeGunData;
class APracticeSoldierCharacter;
class APracticeGunBase;

/**
 * void RegisterNewGun(FGameplayTag InGunTagToRegister, APracticeGunBase* InGunToRegister)
 * : Gun을 Map에 등록시키는 함수
 * 
 * void DeleteCurrentGun(FGameplayTag InGunTagToDelete)
 * : 현재 들고 있는 Gun을 삭제시키는 함수
 * 
 * APracticeGunBase* GetCharacterCarriedGunByTag(FGameplayTag InGunTagToGet) const
 * : Soldier가 현재 가지고 있는 Gun을 태그를 통해 반환하는 함수
 * 
 * APracticeGunBase* GetCharacterCurrentEquippedGun() const;
 * : 현재 장착하고 있는 Gun을 반환하는 함수
 * 
 * void OnHitTargetActor(AActor* HitActor) override
 * : Character에서 CollisionBox가 오버랩 됐을 때 호출되는 함수
 * 
 * void OnHitBoxPulledFromTargetActor(AActor* InteractedActor)
 * : Character에서 CollisionBox의 오버랩이 끝났을 때 호출되는 함수
 * 
 * FGameplayTag CurrentEquippedGunTag
 * : 현재 장착하고 있는 Gun의 Tag
 * 
 * TMap<FGameplayTag, APracticeGunBase*> CharacterCarriedGunMap
 * : Soldier캐릭터가 가지고 다니는 무기의 Map. 여러 개의 무기를 등록하고 다니는 방식으로 계획했으나 개발 방향이 바뀌어 우선 하나의 Gun만 저장됨. 추후 수정 필요
 */

UCLASS()
class PRACTICE_API USoldierCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Practice|Combat") 
	void RegisterNewGun(FGameplayTag InGunTagToRegister, APracticeGunBase* InGunToRegister);

	UFUNCTION(BlueprintCallable, Category = "Practice|Combat")
	void DeleteCurrentGun(FGameplayTag InGunTagToDelete);

	UFUNCTION(BlueprintCallable, Category = "Practice|Combat")
	APracticeGunBase* GetCharacterCarriedGunByTag(FGameplayTag InGunTagToGet) const;

	UPROPERTY(BlueprintReadWrite,Category="Practice|Combat")
	FGameplayTag CurrentEquippedGunTag;

	UFUNCTION(BlueprintCallable, Category = "Practice|Combat")
	APracticeGunBase* GetCharacterCurrentEquippedGun() const;

	UFUNCTION(BlueprintCallable, Category="Practice|Combat")
	float GetSoldierCurrentEquippedGunDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;	
	virtual void OnHitBoxPulledFromTargetActor(AActor* InteractedActor) override;

private:
	TMap<FGameplayTag, APracticeGunBase*> CharacterCarriedGunMap; 

	TWeakObjectPtr<APracticeSoldierCharacter> CachedPracticeSoldierCharacter;

};

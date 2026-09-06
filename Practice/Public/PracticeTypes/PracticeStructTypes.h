#pragma once
// Fill out your copyright notice in the Description page of Project Settings.
//나중에 함수도 구현할 것이므로 cpp파일도 필요해 에디터에서 생성

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "PracticeStructTypes.generated.h"


class UInputMappingContext;
class UPracticeSoldierLinkedAnimLayer;


USTRUCT(BlueprintType)
struct FPracticeAbilitySet //InputTag와 Ability연결. ASC의 OnAbilityInputPressed/Released에서 활용
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPracticeGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};


USTRUCT(BlueprintType)
struct FPracticeGunData //Soldier가 사용하는 Gun에 저장되는 데이터
{
	GENERATED_BODY()

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPracticeSoldierLinkedAnimLayer> GunAnimLayerToLink;*/ //총의 여부에 따라 다른 애니메이션을 동작시키려 했으나 총을 들고 있지 않은 애니메이션이 없었음 

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* GunInputMappingContext;*/ //총을 장착했을 때 적용되는 새로운 매핑 컨텍스트. Fire말고는 달리 다른 Input이 필요치 않아 삭제

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPracticeAbilitySet> DefaultWeaponAbilities; //각 총마다 다른 Ability를 가진다(HitScan, Projectile 등의 방식)

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat GunBaseDamage; //총의 데미지

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Bullets; //총알

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftGunIconTexture; //아이콘. 총이 바뀌면 우측 하단에 총이 바뷔는 것을 볼 수 있다.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) //해당 총의 태그. 총을 습득할 때 등, 총에 대한 연산을 진행할 때 쓰인다.
	FGameplayTag GunTag;

};
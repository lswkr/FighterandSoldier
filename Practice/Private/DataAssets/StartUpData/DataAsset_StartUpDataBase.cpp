// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/PracticeAbilitySystemComponent.h"
#include "Abilities/PracticeGameplayAbility.h"
#include "PracticeGameplayTags.h"

#include "PracticeDebugHelper.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(AcivateOnGivenAbilities,InASCToGive,ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
	if (!InASCToGive->HasMatchingGameplayTag(PracticeGameplayTags::Shared_Status_DontTouchUlt))
	{
		InASCToGive->AddLooseGameplayTag(PracticeGameplayTags::Shared_Status_DontTouchUlt);
		/*
		게임플레이이펙트 중 Ult를 초기화시키는 이펙트는 이 태그가 있으면 발동하지않는다.
		
		레벨업 할 때에는 OnLevelUp함수를 통해 새로운 레벨로 입력 인수를 바꾼 뒤 DA_StartUpData에 저장된 게임플레이 어빌리티와 이펙트를
		모두 그 레벨에 맞게 새로 초기화시키는데 처음 초기화시킬 때 저 태그를 붙여 레벨업 시 Ult 수치는 바꾸지 못하도록 태그를 부여한다.
		*/
	}

}

void UDataAsset_StartUpDataBase::OnLevelUp(UPracticeAbilitySystemComponent* InASCToGive, int32 NewLevel)
{
	check(InASCToGive);
	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				NewLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UPracticeGameplayAbility>>& InAbilitiesToGive, UPracticeAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	
	for (const TSubclassOf<UPracticeGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}

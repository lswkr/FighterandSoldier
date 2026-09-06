// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PracticeAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "PracticeFunctionLibrary.h"
#include "PracticeGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/SoldierUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PracticeGameInstance.h"
#include "Character/PracticeBaseCharacter.h"

#include "PracticeDebugHelper.h"


UPracticeAttributeSet::UPracticeAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitCurrentUlt(1.f);
	InitMaxUlt(1.f);
	InitMaxExp(1.f);
	InitCurrentExp(1.f);
	InitCurrentBullets(0.f);
}

void UPracticeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	
	checkf(PawnUIComponent, TEXT("couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentUltAttribute())
	{
		const float NewCurrentUlt = FMath::Clamp(GetCurrentUlt(), 0.f, GetMaxUlt());

	

		if (NewCurrentUlt == GetMaxUlt()) //Ult의 수치가 최대면 Ult_Full태그를 줘서 궁극기를 사용할 수 있도록하고 Ult_Charging태그를 제거
		{
			UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_UltFull); 
			UPracticeFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_UltCharging);
		}
	
		else //그 이외의 경우에는 Ult_Full태그를 제거하고 Ult_Charging태그를 추가
		{

			UPracticeFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_UltFull);

			UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_UltCharging);

			if (NewCurrentUlt == 0.f) //만약 0이면 Ult_None추가
			{
				UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_UltNone);
			}
			else //아니면 Ult_None제거
			{
				UPracticeFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_UltNone);
			}
		}
		PawnUIComponent->OnCurrentUltChanged.Broadcast(GetCurrentUlt() / GetMaxUlt());
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())	//공격받았을 때
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth()); //데미지 반영

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f) //만약 현재 체력이 0이되면 Shared_Status_Dead태그 부여
		{
			UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PracticeGameplayTags::Shared_Status_Dead);
		}
	}

	

	if (Data.EvaluatedData.Attribute == GetCurrentBulletsAttribute()) 
	{
		const float NewCurrentBullets = FMath::Clamp(GetCurrentBullets(), 0.f, GetMaxBullets());

		SetCurrentBullets(NewCurrentBullets);
		
		
		if (NewCurrentBullets>-1 && NewCurrentBullets<=0) //총알이 다 떨어졌다면
		{
			//Player_Soldier_Status_BulletsEmpty태그 부여. 총알이 있는 발사하는 게임 어빌리티들은 이 태그가 있으면 발동이 안 된다. 
			UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Soldier_Status_BulletsEmpty);
		}
		else //총알이 있으면 Player_Soldier_Status_BulletsEmpty 태그 제거
		{	
			UPracticeFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Soldier_Status_BulletsEmpty);
		}

		if (USoldierUIComponent* SoldierUIComponent = CachedPawnUIInterface->GetSoldierUIComponent()) //총 쏘면 총알의 개수를 위젯에 브로드캐스트
		{
			SoldierUIComponent->OnGunTriggered.Broadcast(NewCurrentBullets);
		}
	}

	if (Data.EvaluatedData.Attribute == GetCurrentExpAttribute())
	{
		const float NewCurrentExp = FMath::Clamp(GetCurrentExp(), 0.f, GetMaxExp());

		SetCurrentExp(NewCurrentExp);

		PawnUIComponent->OnCurrentExpChanged.Broadcast(GetCurrentExp() / GetMaxExp());
	}

	if (Data.EvaluatedData.Attribute == GetExpTakenAttribute())
	{
		const float OldExp = GetCurrentExp();
		const float ExpDone = GetExpTaken();

		const float NewCurrentExp = FMath::Clamp(OldExp + ExpDone, 0.f, GetMaxExp());

		if (NewCurrentExp >= GetMaxExp()) //경험치 다 채우면
		{
			SetCurrentExp(NewCurrentExp);

			UPracticeAbilitySystemComponent* PracticeAbilitySystemComponent = Cast<UPracticeAbilitySystemComponent>(GetOwningAbilitySystemComponent());
			int32 UpdatedLevel = PracticeAbilitySystemComponent->LevelingUpAbilities(); //가지고 있는 어빌리티들의 레벨을 다 올림
			PawnUIComponent->OnCurrentExpChanged.Broadcast(NewCurrentExp);
			PawnUIComponent->OnCurrentLevelChanged.Broadcast(UpdatedLevel);
			if (APracticeBaseCharacter* PlayerCharacter = Cast<APracticeBaseCharacter>(GetOwningActor()))
			{
				PlayerCharacter->ApplyEffectLevelUp(UpdatedLevel);//초기화 이펙트를 레벨업이 되면서 다시 적용시키는 함수
			}
			UPracticeFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_LevelUp);
			UPracticeFunctionLibrary::GetPracticeGameInstance(this)->SetCharacterLevel(UpdatedLevel);
		}
		else
		{
			SetCurrentExp(NewCurrentExp);
			PawnUIComponent->OnCurrentExpChanged.Broadcast(GetCurrentExp() / GetMaxExp());
			UPracticeFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PracticeGameplayTags::Player_Shared_Status_LevelUp);

		}
	}

}

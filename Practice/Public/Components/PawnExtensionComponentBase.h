// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"

/*
* 아래에 있는Helper함수를 Pawn의 모든 액터 컴포넌트에서 활용할 수 있도록
* 모든 Pawn의 액터 컴포넌트들의 Base가 되는 클래스 
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter To GetPawn must be derived from APawn");
		
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningPawnController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter To GetPawn must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};

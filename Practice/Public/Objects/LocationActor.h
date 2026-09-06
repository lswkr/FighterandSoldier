// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationActor.generated.h"

//BossCharacter의 위치가 되는 Actor. 해당 액터는 GetActorOfClass함수로 Spawn되며 이 위치에서 Boss가 Spawn된다.
//TargetPoint를 GetActorOfClass함수로 얻게되면 EnemyLoadAndSpawnBox에서 설정한 TargetPoint도 잡힐 수 있기에
//따로 만들었으며 Boss가 나오는 곳을 꾸미기 위해 StaticMeshComponent를 붙였다.

UCLASS()
class PRACTICE_API ALocationActor : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocationActor();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UStaticMeshComponent* StaticMeshComponent;

};

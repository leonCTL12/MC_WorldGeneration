// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockSpawner.generated.h"

UCLASS()
class MC_WORLDGENERATION_API ABlockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockSpawner();
	FVector origin;

private:
	TMap<FVector, class ABlockBase*> occupied;
	static const int BlockDimension = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnBlock(TSubclassOf<class ABlockBase> blockClass, FVector location);
	void ToggleBlock(FVector location, bool active);
	bool QueryOccupiedLocation(FVector location);

	
};

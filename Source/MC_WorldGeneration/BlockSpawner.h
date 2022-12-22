// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockType.h"
#include "Containers/Map.h"
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
	TMap<FVector, TPair<BlockType, class ABlockBase*>> persistent_occupied;
	static const int BlockDimension = 100;
	class BlockPool* pool;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASoilBlock> soilBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGrassBlock> grassBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWoodBlock> woodBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ALeafBlock> leafwoodBlockClass;
protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnBlock(FVector location, BlockType blockType);
	void DestroyBlock(FVector location);
	bool QueryOccupiedLocation(FVector location);

	
};

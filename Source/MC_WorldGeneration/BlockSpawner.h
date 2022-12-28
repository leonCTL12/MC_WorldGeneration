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
	TMap<FVector2D, TMap<int, TPair<BlockType, class ABlockBase*>>> persistent_occupied;
	static const int BlockDimension = 100;
	class BlockPool* pool;
	class ACharacter* player;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASoilBlock> soilBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGrassBlock> grassBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWoodBlock> woodBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ALeafBlock> leafBlockClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnBlock(FVector location, BlockType blockType);
	void DestoryBlock(FVector location, bool permanent);
	void DisableBlockColumn(FVector2D location);
	void ReEnableBlockColumn(FVector2D location);
	bool QueryOccupiedLocation(FVector location);
	void InitBlockSpawner(int renderDistance);

protected:
	virtual void PostInitializeComponents() override;
private:
	TPair<BlockType, class ABlockBase*>* FetchBlockInfoByLocation(FVector location);
	void AddBlockToMap(TPair<BlockType, class ABlockBase*>*, FVector location);
};

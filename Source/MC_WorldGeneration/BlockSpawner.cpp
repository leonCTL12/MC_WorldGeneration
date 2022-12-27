// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSpawner.h"
#include "BlockPool.h"
#include "Engine/World.h"
#include "BlockBase.h"

// Sets default values
ABlockSpawner::ABlockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlockSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// It is caller's responsibility to ensure that that block exist
TPair<BlockType, class ABlockBase*>* ABlockSpawner::FetchBlockInfoByLocation(FVector location)
{
	return persistent_occupied.Find((FVector2D)location)->Find(location.Z);
}

void ABlockSpawner::AddBlockToMap(TPair<BlockType, class ABlockBase*>* blockInfo, FVector location)
{
	FVector2D location_2d = (FVector2D)location;
	if (!persistent_occupied.Contains(location_2d)) {
		persistent_occupied.Add(location_2d, *(new TMap<int, TPair<BlockType, ABlockBase*>>));
	}
	persistent_occupied.Find(location_2d)->Add(location.Z, *blockInfo);
}

//This is called before begin play
void ABlockSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	origin = GetActorLocation();
	pool = new BlockPool(grassBlockClass, soilBlockClass);
}

// Called every frame
void ABlockSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Spawn a new block at the location

//It is World Generator's responsibility to ensure that each location only has one block
void ABlockSpawner::SpawnBlock(FVector location, BlockType blockType )
{
	ABlockBase* block = nullptr;
	if (QueryOccupiedLocation(location)) {
		auto blockInfo = FetchBlockInfoByLocation(location);
	    block = pool->CreateBlock(GetWorld(), blockInfo->Key);
	}
	else {
		block = pool->CreateBlock(GetWorld(), blockType);
		TPair<BlockType, ABlockBase* > info(blockType, block);
		AddBlockToMap(&info, location);
	}

	block->SetActorLocation(location * BlockDimension + origin);

}


void ABlockSpawner::DestoryBlock(FVector location, bool permanent = false)
{
	if (!QueryOccupiedLocation(location)) {
		return;
	}

	if (permanent) {
		//TODO: Implement Permanent Destroy when mining mechanism is implemented
	}
	else {
		auto blockInfo = FetchBlockInfoByLocation(location);
		pool->DestroyBlock(blockInfo->Value, blockInfo->Key);
	}
}


void ABlockSpawner::DisableBlockColumn(FVector2D location)
{
	if (!persistent_occupied.Contains(location)) {
		return;
	}

	for (auto& blockInfoPair : *persistent_occupied.Find(location)) {
		auto blockInfo = (blockInfoPair.Value);
		pool->DestroyBlock(blockInfo.Value, blockInfo.Key);
	}
}

bool ABlockSpawner::QueryOccupiedLocation(FVector location)
{
	FVector2D v2d = FVector2D(location);
	if (!persistent_occupied.Contains(v2d)) { return false; }

	return persistent_occupied.Find(v2d)->Contains(location.Z);
}
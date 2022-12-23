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

//This is called before begin play
void ABlockSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	origin = GetActorLocation();
	pool = new BlockPool(grassBlockClass);
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
		auto blockInfo = persistent_occupied.Find(location);
	    block = pool->CreateBlock(GetWorld(), blockInfo->Key);
	}
	else {
		block = pool->CreateBlock(GetWorld(), blockType);
		TPair<BlockType, ABlockBase* > pair(blockType, block);
		persistent_occupied.Add(location, pair);
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
		auto blockInfo = persistent_occupied.Find(location);
		pool->DestroyBlock(blockInfo->Value, blockInfo->Key);
	}
}


bool ABlockSpawner::QueryOccupiedLocation(FVector location)
{
	return persistent_occupied.Contains(location);
}
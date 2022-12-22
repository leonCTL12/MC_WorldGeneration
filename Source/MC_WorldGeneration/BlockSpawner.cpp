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

//When this is called, we are sure that 
void ABlockSpawner::SpawnBlock(FVector location, BlockType blockType = none )
{
	//Spawning Old Block
	if (blockType == none) {

	}
	else { //Spawning new Block
		if (QueryOccupiedLocation(location)) {
			return;
		}
		ABlockBase* block = pool->CreateBlock(GetWorld(), blockType);
		block->SetActorLocation(location*BlockDimension + origin);
		TPair<BlockType, ABlockBase* > pair(blockType, block);
		persistent_occupied.Add(location, pair);
	}

}


void ABlockSpawner::DestroyBlock(FVector location)
{
	/*if (!QueryOccupiedLocation(location)) {
		return;
	}
	ABlockBase** block_ptr_2 = persistent_occupied.Find(location);
	(*block_ptr_2)->SetActive(active);*/
}


bool ABlockSpawner::QueryOccupiedLocation(FVector location)
{
	return persistent_occupied.Contains(location);
}
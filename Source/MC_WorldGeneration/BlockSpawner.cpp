// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSpawner.h"
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
	origin = GetActorLocation();

}

// Called every frame
void ABlockSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABlockSpawner::SpawnBlock(TSubclassOf<ABlockBase> blockClass, FVector location)
{
	if (occupied.Contains(location)) {
		UE_LOG(LogTemp, Warning, TEXT("location occupied"));
		ToggleBlock(location, true);
		return;
	}
	occupied.Add(location, GetWorld()->SpawnActor<ABlockBase>(blockClass, origin + location * BlockDimension, FRotator(0)));
}


void ABlockSpawner::ToggleBlock(FVector location, bool active)
{
	if (!occupied.Contains(location)) {
		return;
	}
	ABlockBase** block_ptr_2 = occupied.Find(location);
	(*block_ptr_2)->SetActive(active);
}

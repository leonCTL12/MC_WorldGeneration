// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
#include "GrassBlock.h"
#include "WorldGenerator.h"

// Sets default values
AWorldGenerator::AWorldGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();

	origin = GetActorLocation() - FVector(worldWidth/2,worldLength/2,0);

	GenerateWorld();
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldGenerator::GenerateWorld()
{
	GenerateLand();
}

void AWorldGenerator::GenerateLand()
{
	FRotator Rotation(0);
	//GetWorld()->SpawnActor<ASoilBlock>(soilBlockClass, origin, Rotation);
	
	UWorld* world = GetWorld();

	FVector currentSpawnPoint = origin;

	for (int w = 0; w < worldWidth; w++) {
		currentSpawnPoint += FVector(BlockDimension, 0, 0);
		currentSpawnPoint.Y = origin.Y;
		for (int l = 0; l < worldLength; l++) {
			world->SpawnActor<ASoilBlock>(soilBlockClass, currentSpawnPoint, Rotation);
			currentSpawnPoint += FVector(0, BlockDimension, 0);
		}
	}

}

void AWorldGenerator::GenerateTree()
{

}

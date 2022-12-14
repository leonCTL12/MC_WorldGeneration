// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
#include "GrassBlock.h"
#include "BlockBase.h"
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
	UE_LOG(LogTemp, Warning, TEXT("ZZ1"));

	origin = GetActorLocation();

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
	GenerateMountain();
}

void AWorldGenerator::GenerateLand()
{

	FRotator Rotation(0);
	
	UWorld* world = GetWorld();

	FVector currentSpawnPoint(0);

	for (int w = 0; w < worldWidth; w++) {
		currentSpawnPoint.Y = 0;

		for (int l = 0; l < worldLength; l++) {
			SpawnBlock(soilBlockClass, currentSpawnPoint);
			currentSpawnPoint += FVector(0, 1, 0);
		}
		currentSpawnPoint += FVector(1, 0, 0);
	}
}

void AWorldGenerator::GenerateMountain()
{
	int numberOfMountain = FMath::RandRange(minNumMountain, maxNumMountain);

	for (int i = 0; i < numberOfMountain; i++) {

		FVector peakPoint = FVector(FMath::RandRange(0, worldLength), FMath::RandRange(0, worldWidth), FMath::RandRange(0, maxMountainHeight));
		BuildMountain(peakPoint);
	}
}

void AWorldGenerator::BuildMountain(FVector peakPoint)
{

	FRotator Rotation(0);
	UWorld* world = GetWorld();
	
	int height = peakPoint.Z;

	int currentExpansion = 1;
	while (height > 1) {
		height--;

		currentExpansion += FMath::RandRange(0,2);

		for (int widthDelta = -currentExpansion; widthDelta < currentExpansion; widthDelta++) {
			for (int lengthDelta = -currentExpansion; lengthDelta < currentExpansion; lengthDelta++) {

				FVector spawnPoint = peakPoint + FVector(lengthDelta, widthDelta, 0);
				spawnPoint.Z = height;

				UE_LOG(LogTemp, Warning, TEXT("spawn location: %s"), *spawnPoint.ToString());
				FMath::Clamp<int>(spawnPoint.X, 0, worldLength - 1);
				FMath::Clamp<int>(spawnPoint.Y, 0, worldWidth - 1);
				SpawnBlock(grassBlockClass, spawnPoint);
			}
		}
	}
}



void AWorldGenerator::SpawnBlock(TSubclassOf<ABlockBase> blockClass , FVector location)
{
	GetWorld()->SpawnActor<ABlockBase>(blockClass, origin+ location * BlockDimension, FRotator(0));
}


void AWorldGenerator::GenerateTree()
{

}

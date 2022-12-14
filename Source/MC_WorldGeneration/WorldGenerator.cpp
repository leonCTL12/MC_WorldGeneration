// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
#include "GrassBlock.h"
#include "WorldGenerator.h"

#define LOG(x) ;

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

	origin = GetActorLocation() - FVector(worldWidth * BlockDimension /2,worldLength * BlockDimension /2,0);

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

void AWorldGenerator::GenerateMountain()
{
	int numberOfMountain = FMath::RandRange(0, maxNumMountain);
	FVector2D origin_2D(origin.X, origin.Y);
	for (int i = 0; i < numberOfMountain; i++) {
		FVector2D peakPoint_2D = origin_2D + FVector2D(FMath::RandRange(0, worldLength)*BlockDimension, FMath::RandRange(0, worldWidth)*BlockDimension);
		BuildMountain(peakPoint_2D);
	}
}

void AWorldGenerator::BuildMountain(FVector2D peakPoint_2D)
{
	int height = FMath::RandRange(1, maxMountainHeight);

	FRotator Rotation(0);
	FVector peakPoint(peakPoint_2D.X, peakPoint_2D.Y, height*BlockDimension + origin.Z);
	UWorld* world = GetWorld();
	
	UE_LOG(LogTemp, Warning, TEXT("Height = %d"), height);

	//world->SpawnActor<AGrassBlock>(grassBlockClass, peakPoint, Rotation);

	int currentExpansion = 1;
	while (height > 1) {
		height--;

		currentExpansion += FMath::RandRange(0,2);

		for (int width = -currentExpansion; width < currentExpansion; width++) {
			for (int length = -currentExpansion; length < currentExpansion; length++) {

				FVector spawnPoint = peakPoint + FVector(length * BlockDimension, width * BlockDimension, 0); 
				spawnPoint.Z = height * BlockDimension + origin.Z;
				UE_LOG(LogTemp, Warning, TEXT("spawn location: %s"), *spawnPoint.ToString());
				world->SpawnActor<AGrassBlock>(grassBlockClass, spawnPoint, Rotation);
			}
		}
	}
}




void AWorldGenerator::GenerateTree()
{

}

// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
#include "GrassBlock.h"
#include "BlockBase.h"
#include "WoodBlock.h"
#include "LeafBlock.h"
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
	GenerateTrees();
}

void AWorldGenerator::GenerateLand()
{

	FRotator Rotation(0);
	
	UWorld* world = GetWorld();

	FVector currentSpawnPoint(0);

	for (int w = 0; w < worldWidth; w++) {
		currentSpawnPoint.Y = 0;

		for (int l = 0; l < worldLength; l++) {
			SpawnBlock(grassBlockClass, currentSpawnPoint);
			currentSpawnPoint += FVector(0, 1, 0);
		}
		currentSpawnPoint += FVector(1, 0, 0);
	}
}

void AWorldGenerator::GenerateMountain()
{
	int numberOfMountain = FMath::RandRange(minNumMountain, maxNumMountain);

	for (int i = 0; i < numberOfMountain; i++) {

		FVector peakPoint = FVector(FMath::RandRange(0, worldLength-1), FMath::RandRange(0, worldWidth-1), FMath::RandRange(0, maxMountainHeight));
		BuildMountain(peakPoint);
	}
}

void AWorldGenerator::BuildMountain(FVector peakPoint)
{

	FRotator Rotation(0);
	UWorld* world = GetWorld();
	
	int height = peakPoint.Z;

	//probability to expand (in percent)
	const int expandProbability = 90;

	int currentExpansion = 1;
	int previousExpansion = currentExpansion;
	while (height > 1) {
		height--;

		if (randomWeightedBool(expandProbability)) {
			currentExpansion += FMath::RandRange(1, 2);
		}

		
		for (int widthDelta = -currentExpansion; widthDelta < currentExpansion+1; widthDelta++) {
			for (int lengthDelta = -currentExpansion; lengthDelta < currentExpansion+1; lengthDelta++) {
				
				FVector spawnPoint = peakPoint + FVector(lengthDelta, widthDelta, 0);
				spawnPoint.Z = height;

				spawnPoint.X = FMath::Clamp<int>(spawnPoint.X, 0, worldLength - 1);
				spawnPoint.Y = FMath::Clamp<int>(spawnPoint.Y, 0, worldWidth - 1);
				
				if (height == peakPoint.Z-1 || FMath::Abs(widthDelta) > previousExpansion || FMath::Abs(lengthDelta) > previousExpansion) {
					SpawnBlock(grassBlockClass, spawnPoint);
				}
				else {
					SpawnBlock(soilBlockClass, spawnPoint);
				}
			}
		}

		previousExpansion = currentExpansion;
	}
}

void AWorldGenerator::GenerateTrees()
{
	int numberOfTree = FMath::RandRange(minNumTree, maxNumTree);

	for (int i = 0; i < numberOfTree; i++) {

		FVector rootPoint = FVector(FMath::RandRange(0, worldLength-1), FMath::RandRange(0, worldWidth-1),1);

		while (occupied.Contains(rootPoint)) {
			rootPoint.Z++;
		}

		BuildTree(rootPoint);
	}
}

void AWorldGenerator::BuildTree(FVector spawnPoint)
{
	int treeHeight = FMath::RandRange(minTreeHeight, maxTreeHeight);
	for (int i = 0; i < treeHeight; i++) {
		SpawnBlock(woodBlockClass, spawnPoint);
		spawnPoint.Z++;
	}
	spawnPoint.Z--;
	BuildTreeLeaf(spawnPoint);
	
}

void AWorldGenerator::BuildTreeLeaf(FVector topPoint)
{
	//Hardcoded procedure to spawn tree leaf
#pragma region Top Layer
	
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y, topPoint.Z+1));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y+1, topPoint.Z+1));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y-1, topPoint.Z+1));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X+1, topPoint.Y, topPoint.Z+1));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X-1, topPoint.Y, topPoint.Z+1));
	
#pragma endregion

#pragma region Second Layer
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y + 1, topPoint.Z));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y - 1, topPoint.Z));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y, topPoint.Z));
	SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y, topPoint.Z));
	const int probSideLeaf = 30;
	if (randomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y-1, topPoint.Z));
	}
	if (randomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y + 1, topPoint.Z));
	}
	if (randomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y - 1, topPoint.Z));
	}
	if (randomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y + 1, topPoint.Z));
	}

#pragma endregion

#pragma region Third Layer
	for (int i = topPoint.X - 2; i <= topPoint.X + 2; i++) {
		for (int j = topPoint.Y - 2; j <= topPoint.Y + 2; j++) {

			if (i == topPoint.X - 2 && (j == topPoint.Y - 2) && randomWeightedBool(30)) {
				continue;
			}
			else if (i == topPoint.X + 2 && (j == topPoint.Y - 2) && randomWeightedBool(30)) {
				continue;
			}
			else if (i == topPoint.X - 2 && (j == topPoint.Y + 2) && randomWeightedBool(30)) {
				continue;
			}
			else if (i == topPoint.X + 2 && (j == topPoint.Y + 2) && randomWeightedBool(30)) {
				continue;
			}

			SpawnBlock(leafwoodBlockClass, FVector(i, j, topPoint.Z - 1));
			SpawnBlock(leafwoodBlockClass, FVector(i, j, topPoint.Z - 2));
		}
	}

#pragma endregion
}


void AWorldGenerator::SpawnBlock(TSubclassOf<ABlockBase> blockClass , FVector location)
{
	if (occupied.Contains(location)) {
		return;
	}
	occupied.Add(location);
	GetWorld()->SpawnActor<ABlockBase>(blockClass, origin+ location * BlockDimension, FRotator(0));
}

bool AWorldGenerator::randomWeightedBool(int percentage)
{
	return percentage >= FMath::RandRange(0, 100);
}


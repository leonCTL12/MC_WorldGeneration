// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
#include "GrassBlock.h"
#include "BlockBase.h"
#include "WoodBlock.h"
#include "LeafBlock.h"
#include "WorldGenerator.h"	
#include "MyMathUtility.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "GenericPlatform/GenericPlatformMath.h"

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
	UE_LOG(LogTemp, Warning, TEXT("ZZ2"));

	origin = GetActorLocation();
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	XUpperBound = renderDistance * 2;
	XLowerBound = -1;
	YUpperBound = renderDistance*2;
	YLowerBound = -1; 

	GenerateWorld();
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector playerLocation = player->GetActorLocation();

	playerLocation =  (playerLocation - origin) / 100;
	playerLocation.X = FGenericPlatformMath::RoundToInt(playerLocation.X);
	playerLocation.Y = FGenericPlatformMath::RoundToInt(playerLocation.Y);
	
	CheckMapExpansion(playerLocation);
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

	for (int w = 0; w < renderDistance*2; w++) {
		currentSpawnPoint.Y = 0;

		for (int l = 0; l < renderDistance*2; l++) {
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

		FVector peakPoint = FVector(FMath::RandRange(0, renderDistance*2-1), FMath::RandRange(0, renderDistance*2-1), FMath::RandRange(0, maxMountainHeight));
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

		if (MyMathUtility::RandomWeightedBool(expandProbability)) {
			currentExpansion += FMath::RandRange(1, 2);
		}
		
		for (int widthDelta = -currentExpansion; widthDelta < currentExpansion+1; widthDelta++) {
			for (int lengthDelta = -currentExpansion; lengthDelta < currentExpansion+1; lengthDelta++) {
				
				FVector spawnPoint = peakPoint + FVector(lengthDelta, widthDelta, 0);
				spawnPoint.Z = height;

				spawnPoint.X = FMath::Clamp<int>(spawnPoint.X, 0, renderDistance*2 - 1);
				spawnPoint.Y = FMath::Clamp<int>(spawnPoint.Y, 0, renderDistance*2 - 1);
				
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

		FVector rootPoint = FVector(FMath::RandRange(0, renderDistance*2-1), FMath::RandRange(0, renderDistance*2-1),1);

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
	if (MyMathUtility::RandomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y-1, topPoint.Z));
	}
	if (MyMathUtility::RandomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y + 1, topPoint.Z));
	}
	if (MyMathUtility::RandomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y - 1, topPoint.Z));
	}
	if (MyMathUtility::RandomWeightedBool(30)) {
		SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y + 1, topPoint.Z));
	}

#pragma endregion

#pragma region Third Layer
	for (int i = topPoint.X - 2; i <= topPoint.X + 2; i++) {
		for (int j = topPoint.Y - 2; j <= topPoint.Y + 2; j++) {

			if (i == topPoint.X - 2 && (j == topPoint.Y - 2) && MyMathUtility::RandomWeightedBool(30)) {
				continue;
			}
			else if (i == topPoint.X + 2 && (j == topPoint.Y - 2) && MyMathUtility::RandomWeightedBool(30)) {
				continue;
			}
			else if (i == topPoint.X - 2 && (j == topPoint.Y + 2) && MyMathUtility::RandomWeightedBool(30)) {
				continue;
			}
			else if (i == topPoint.X + 2 && (j == topPoint.Y + 2) && MyMathUtility::RandomWeightedBool(30)) {
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
		UE_LOG(LogTemp, Warning, TEXT("location occupied"));
		ToggleBlock(location, true);
		return;
	}

	occupied.Add(location, GetWorld()->SpawnActor<ABlockBase>(blockClass, origin + location * BlockDimension, FRotator(0)) );
}

void AWorldGenerator::ToggleBlock(FVector location, bool active)
{
	if (!occupied.Contains(location)) {
		return;
	}
	ABlockBase** block_ptr_2 = occupied.Find(location);
	(*block_ptr_2)->SetActive(active);
}

void AWorldGenerator::CheckMapExpansion(FVector normalizedPlayerLocation)
{
	if (FMath::Abs(XUpperBound - normalizedPlayerLocation.X) <= expansionTriggerDistance) {
		ExpandMap(XUp);
	} else if (FMath::Abs(XLowerBound - normalizedPlayerLocation.X) <= expansionTriggerDistance) {
		ExpandMap(XLow);
	}

	if (FMath::Abs(YUpperBound - normalizedPlayerLocation.Y) <= expansionTriggerDistance) {
		ExpandMap(YUp);
	} else if (FMath::Abs(YLowerBound - normalizedPlayerLocation.Y) <= expansionTriggerDistance) {
		ExpandMap(YLow);
	}
}

void AWorldGenerator::ExpandMap(ExpandDirection direction)
{
	switch (direction)
	{
	case XUp:
		UE_LOG(LogTemp, Warning, TEXT("Expand XUp"));

		for (int y = YLowerBound+1; y < YUpperBound; y++) {
			for (int x = XUpperBound; x < XUpperBound + dynamicGenChunkSize; x++) {
				SpawnBlock(grassBlockClass, FVector(x, y, 0));
			}

			for (int x = XLowerBound + 1; x < XLowerBound + dynamicGenChunkSize + 1; x++) {
				ToggleBlock(FVector(x, y, 0), false);
			}
		}

		XUpperBound += dynamicGenChunkSize;
		XLowerBound += dynamicGenChunkSize;

		break;
	case XLow:
		for (int y = YLowerBound+1; y < YUpperBound; y++) {
			for (int x = XLowerBound; x > XLowerBound - dynamicGenChunkSize; x--) {
				UE_LOG(LogTemp, Warning, TEXT("X= %d, Y= %d"), x, y);
				SpawnBlock(grassBlockClass, FVector(x, y, 0));
			}

			for (int x = XUpperBound - 1; x > XUpperBound - dynamicGenChunkSize - 1; x--) {
				ToggleBlock(FVector(x, y, 0), false);
			}
		}
		XUpperBound-= dynamicGenChunkSize;
		XLowerBound-= dynamicGenChunkSize;
		break;	

	case YUp:
		UE_LOG(LogTemp, Warning, TEXT("Expand YUp"));

		for (int x = XLowerBound+1; x < XUpperBound; x++) {
			for (int y = YUpperBound; y < YUpperBound + dynamicGenChunkSize; y++) {
				SpawnBlock(grassBlockClass, FVector(x, y, 0));
			}

			for (int y = YLowerBound + 1; y < YLowerBound + dynamicGenChunkSize + 1; y++) {
				ToggleBlock(FVector(x, y, 0), false);
			}
		}

		YUpperBound+= dynamicGenChunkSize;
		YLowerBound+= dynamicGenChunkSize;

		break;
	case YLow:
		UE_LOG(LogTemp, Warning, TEXT("Expand YLow"));

		for (int x = XLowerBound + 1; x < XUpperBound; x++) {
			for (int y = YLowerBound; y > YLowerBound - dynamicGenChunkSize; y--) {
				SpawnBlock(grassBlockClass, FVector(x, y, 0));
			}
			for (int y = YUpperBound - 1; y > YUpperBound - dynamicGenChunkSize - 1; y--) {
				ToggleBlock(FVector(x, y, 0), false);
			}
		}

		YUpperBound-=dynamicGenChunkSize;
		YLowerBound -= dynamicGenChunkSize;

		break;

	default:
		break;
	}
}


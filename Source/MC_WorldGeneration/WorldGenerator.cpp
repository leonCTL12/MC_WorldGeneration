// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
#include "GrassBlock.h"
#include "BlockBase.h"
#include "WoodBlock.h"
#include "LeafBlock.h"
#include "BlockSpawner.h"
#include "WorldGenerator.h"	
#include "MyMathUtility.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
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
	ensure(blockSpawner);
	UE_LOG(LogTemp, Warning, TEXT("ZZ2"));

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

	playerLocation =  (playerLocation - blockSpawner->origin) / 100;
	playerLocation.X = FGenericPlatformMath::RoundToInt(playerLocation.X);
	playerLocation.Y = FGenericPlatformMath::RoundToInt(playerLocation.Y);
	
	CheckMapExpansion(playerLocation);
}

void AWorldGenerator::GenerateWorld()
{
	GenerateLand();
	//GenerateMountain(FVector2D(XLowerBound, YLowerBound), FVector2D(XUpperBound, YUpperBound));
	//GenerateTrees(FVector2D(XLowerBound, YLowerBound), FVector2D(XUpperBound, YUpperBound));
}

void AWorldGenerator::GenerateLand()
{
	FRotator Rotation(0);
	
	FVector currentSpawnPoint(0);

	for (int w = 0; w < renderDistance*2; w++) {
		currentSpawnPoint.Y = 0;
		for (int l = 0; l < renderDistance*2; l++) {
			if (!blockSpawner) {
				UE_LOG(LogTemp, Error, TEXT("No Spawner!!!!"));
				break;
			}
			else {
				blockSpawner->SpawnBlock(currentSpawnPoint, grass);
				currentSpawnPoint += FVector(0, 1, 0);
			}
		}
		currentSpawnPoint += FVector(1, 0, 0);
	}
}

#pragma region Mountain Generation
void AWorldGenerator::GenerateMountain(FVector2D minPtr, FVector2D maxPtr)
{
	int area = MyMathUtility::AreaBoundedByTwoPoints(minPtr, maxPtr);

	int maxNumMountain = MyMathUtility::DensityToCount(maxTreeDensity, area, DensityDivisor);
	int minNumMountain = MyMathUtility::DensityToCount(minTreeDensity, area, DensityDivisor);

	int numberOfMountain = FMath::RandRange(minNumMountain, maxNumMountain);

	for (int i = 0; i < numberOfMountain; i++) {

		FVector peakPoint = FVector(FMath::RandRange(minPtr.X, maxPtr.X), FMath::RandRange(minPtr.Y, maxPtr.Y), FMath::RandRange(0, maxMountainHeight));
		BuildMountain(peakPoint);
	}
}

void AWorldGenerator::BuildMountain(FVector peakPoint)
{
	//FRotator Rotation(0);
	//UWorld* world = GetWorld();

	//int height = peakPoint.Z;

	////probability to expand (in percent)
	//const int expandProbability = 90;

	//int currentExpansion = 1;
	//int previousExpansion = currentExpansion;
	//while (height > 1) {
	//	height--;

	//	if (MyMathUtility::RandomWeightedBool(expandProbability)) {
	//		currentExpansion += FMath::RandRange(1, 2);
	//	}

	//	for (int widthDelta = -currentExpansion; widthDelta < currentExpansion + 1; widthDelta++) {
	//		for (int lengthDelta = -currentExpansion; lengthDelta < currentExpansion + 1; lengthDelta++) {

	//			FVector spawnPoint = peakPoint + FVector(lengthDelta, widthDelta, 0);
	//			spawnPoint.Z = height;

	//			if (height == peakPoint.Z - 1 || FMath::Abs(widthDelta) > previousExpansion || FMath::Abs(lengthDelta) > previousExpansion) {
	//				blockSpawner->SpawnBlock(grassBlockClass, spawnPoint);
	//			}
	//			else {
	//				blockSpawner->SpawnBlock(soilBlockClass, spawnPoint);
	//			}
	//		}
	//	}

	//	previousExpansion = currentExpansion;
	//}
}
#pragma endregion

#pragma region Tree Generation
void AWorldGenerator::GenerateTrees(FVector2D minPtr, FVector2D maxPtr)
{

	int area = MyMathUtility::AreaBoundedByTwoPoints(minPtr, maxPtr);

	int minNumTree = MyMathUtility::DensityToCount(minTreeDensity, area, DensityDivisor);
	int maxNumTree = MyMathUtility::DensityToCount(maxTreeDensity, area, DensityDivisor);

	int numberOfTree = FMath::RandRange(minNumTree, maxNumTree);

	for (int i = 0; i < numberOfTree; i++) {

		FVector rootPoint = FVector(FMath::RandRange(minPtr.X, maxPtr.X), FMath::RandRange(minPtr.Y, maxPtr.Y), 1);

		while (blockSpawner->QueryOccupiedLocation(rootPoint)) {
			rootPoint.Z++;
		}

		BuildTree(rootPoint);
	}
}

void AWorldGenerator::BuildTree(FVector spawnPoint)
{
	/*int treeHeight = FMath::RandRange(minTreeHeight, maxTreeHeight);
	for (int i = 0; i < treeHeight; i++) {
		blockSpawner->SpawnBlock(woodBlockClass, spawnPoint);
		spawnPoint.Z++;
	}
	spawnPoint.Z--;
	BuildTreeLeaf(spawnPoint);*/

}

void AWorldGenerator::BuildTreeLeaf(FVector topPoint)
{
	//Hardcoded procedure to spawn tree leaf
#pragma region Top Layer

	/*blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y, topPoint.Z + 1));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y + 1, topPoint.Z + 1));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y - 1, topPoint.Z + 1));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y, topPoint.Z + 1));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y, topPoint.Z + 1));

#pragma endregion

#pragma region Second Layer
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y + 1, topPoint.Z));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X, topPoint.Y - 1, topPoint.Z));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y, topPoint.Z));
	blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y, topPoint.Z));
	const int probSideLeaf = 30;
	if (MyMathUtility::RandomWeightedBool(30)) {
		blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y - 1, topPoint.Z));
	}
	if (MyMathUtility::RandomWeightedBool(30)) {
		blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X - 1, topPoint.Y + 1, topPoint.Z));
	}
	if (MyMathUtility::RandomWeightedBool(30)) {
		blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y - 1, topPoint.Z));
	}
	if (MyMathUtility::RandomWeightedBool(30)) {
		blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(topPoint.X + 1, topPoint.Y + 1, topPoint.Z));
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

			blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(i, j, topPoint.Z - 1));
			blockSpawner->SpawnBlock(leafwoodBlockClass, FVector(i, j, topPoint.Z - 2));
		}
	}

#pragma endregion*/
}
#pragma endregion


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

		for (int y = YLowerBound + 1; y < YUpperBound; y++) {
			for (int x = XLowerBound + 1; x < XLowerBound + 1 + dynamicGenChunkSize; x++) {
				blockSpawner->DestoryBlock(FVector(x, y, 0), false);
			}

			for (int x = XUpperBound; x < XUpperBound + dynamicGenChunkSize; x++) {
				blockSpawner->SpawnBlock(FVector(x, y, 0), grass);
			}

		}

		XUpperBound += dynamicGenChunkSize;
		XLowerBound += dynamicGenChunkSize;

		GenerateMountain(FVector2D(XUpperBound - dynamicGenChunkSize, YLowerBound), FVector2D(XUpperBound, YUpperBound));
		GenerateTrees(FVector2D(XUpperBound - dynamicGenChunkSize, YLowerBound), FVector2D(XUpperBound, YUpperBound));

		break;
	case XLow:
		for (int y = YLowerBound + 1; y < YUpperBound; y++) {
			for (int x = XUpperBound - 1; x > XUpperBound - dynamicGenChunkSize - 1; x--) {
				blockSpawner->DestoryBlock(FVector(x, y, 0), false);
			}

			for (int x = XLowerBound; x > XLowerBound - dynamicGenChunkSize; x--) {
				blockSpawner->SpawnBlock(FVector(x, y, 0), grass);
			}

		}
		XUpperBound -= dynamicGenChunkSize;
		XLowerBound -= dynamicGenChunkSize;

		GenerateMountain(FVector2D(XLowerBound, YLowerBound), FVector2D(XLowerBound + dynamicGenChunkSize, YUpperBound));
		GenerateTrees(FVector2D(XLowerBound, YLowerBound), FVector2D(XLowerBound + dynamicGenChunkSize, YUpperBound));

		break;

	case YUp:
		UE_LOG(LogTemp, Warning, TEXT("Expand YUp"));

		for (int x = XLowerBound + 1; x < XUpperBound; x++) {
			for (int y = YLowerBound + 1; y < YLowerBound + dynamicGenChunkSize + 1; y++) {
				blockSpawner->DestoryBlock(FVector(x, y, 0), false);
			}

			for (int y = YUpperBound; y < YUpperBound + dynamicGenChunkSize; y++) {
				blockSpawner->SpawnBlock(FVector(x, y, 0), grass);
			}
		}

		YUpperBound += dynamicGenChunkSize;
		YLowerBound += dynamicGenChunkSize;

		break;
	case YLow:
		UE_LOG(LogTemp, Warning, TEXT("Expand YLow"));

		for (int x = XLowerBound + 1; x < XUpperBound; x++) {
			for (int y = YUpperBound - 1; y > YUpperBound - dynamicGenChunkSize - 1; y--) {
				blockSpawner->DestoryBlock(FVector(x, y, 0), false);
			}
			for (int y = YLowerBound; y > YLowerBound - dynamicGenChunkSize; y--) {
				blockSpawner->SpawnBlock(FVector(x, y, 0), grass);
			}
			
		}

		YUpperBound -= dynamicGenChunkSize;
		YLowerBound -= dynamicGenChunkSize;

		break;

	default:
		break;
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGenerator.generated.h"

UCLASS()
class MC_WORLDGENERATION_API AWorldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldGenerator();

private:
#pragma region World
	UPROPERTY(EditAnywhere)
		int worldWidth = 40;
	UPROPERTY(EditAnywhere)
		int worldLength = 40;
	UPROPERTY(EditAnywhere)
		float renderDistance = 1000;
#pragma endregion

#pragma region Mountain
	UPROPERTY(EditAnywhere)
		int maxNumMountain = 19;
	UPROPERTY(EditAnywhere)
		int minNumMountain = 19;
	UPROPERTY(EditAnywhere)
		int maxMountainHeight = 5;
#pragma endregion

#pragma region Tree
	UPROPERTY(EditAnywhere)
		int maxNumTree = 19;
	UPROPERTY(EditAnywhere)
		int minNumTree = 19;

	UPROPERTY(EditAnywhere)
		int maxTreeHeight = 8;
	const int minTreeHeight = 5;
#pragma endregion


#pragma region Block
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASoilBlock> soilBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGrassBlock> grassBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWoodBlock> woodBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ALeafBlock> leafwoodBlockClass;

#pragma endregion

	static const int BlockDimension = 100;
	TSet<FVector> occupied;
	FVector origin;

	float XLowerBound;
	float YLowerBound;
	float XUpperBound;
	float YUpperBound;

	class ACharacter* player;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateWorld();
private:
	void GenerateLand();
	void GenerateMountain();

	void SpawnBlock(TSubclassOf<class ABlockBase> blockClass, FVector location);

	void BuildMountain(FVector peakPoint);
	void GenerateTrees();
	void BuildTree(FVector rootPoint);
	void BuildTreeLeaf(FVector topPoint);
	bool randomWeightedBool(int percentage);
};

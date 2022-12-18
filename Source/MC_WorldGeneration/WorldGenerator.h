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
	enum ExpandDirection {XUp, XLow, YUp,YLow};
private:
#pragma region World
	//This is the normalized render distance
	UPROPERTY(EditAnywhere)
		int renderDistance = 5;
	UPROPERTY(EditAnywhere)
		int expansionTriggerDistance = 1;
	UPROPERTY(EditAnywhere)
		int dynamicGenChunkSize = 2;
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
	TMap<FVector,class ABlockBase*> occupied;
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

	void SpawnBlock(TSubclassOf<ABlockBase> blockClass, FVector location);
	void ToggleBlock(FVector location, bool active);

	void BuildMountain(FVector peakPoint);
	void GenerateTrees();
	void BuildTree(FVector rootPoint);
	void BuildTreeLeaf(FVector topPoint);
	void CheckMapExpansion(FVector normalisedPlayerLocation);
	void ExpandMap(ExpandDirection direction);
};

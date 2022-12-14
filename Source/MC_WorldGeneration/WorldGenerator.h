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
	UPROPERTY(EditAnywhere)
		int worldWidth = 40;
	UPROPERTY(EditAnywhere)
		int worldLength = 40;

	UPROPERTY(EditAnywhere)
		int maxNumMountain = 19;

	UPROPERTY(EditAnywhere)
		int minNumMountain = 19;
	UPROPERTY(EditAnywhere)
		int maxMountainHeight = 5;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASoilBlock> soilBlockClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGrassBlock> grassBlockClass;

	static const int BlockDimension = 100;

	FVector origin;

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
	void GenerateTree();
};

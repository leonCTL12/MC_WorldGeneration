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
		int width = 4;
	UPROPERTY(EditAnywhere)
		int height = 4;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASoilBlock> soilBlockClass;

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
	void GenerateTree();
};

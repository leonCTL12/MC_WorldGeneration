// Fill out your copyright notice in the Description page of Project Settings.

#include "SoilBlock.h"
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
}

void AWorldGenerator::GenerateLand()
{
	FRotator Rotation(0);
	GetWorld()->SpawnActor<ASoilBlock>(soilBlockClass, origin, Rotation);
}

void AWorldGenerator::GenerateTree()
{

}

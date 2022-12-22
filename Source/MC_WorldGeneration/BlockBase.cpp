// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	if (bDefaultDisable) {
		SetActive(false);
	}
}

void ABlockBase::Enable(FVector location)
{
	alive = true;
	SetActive(true);
	SetActorLocation(location);
}

void ABlockBase::Disable()
{
	alive = false;
	SetActive(false);
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockBase::SetActive(bool active)
{
	if (!bAlwaysDisableTick) {
		SetActorTickEnabled(active);
	}
	SetActorHiddenInGame(!active);
	SetActorEnableCollision(active);
}



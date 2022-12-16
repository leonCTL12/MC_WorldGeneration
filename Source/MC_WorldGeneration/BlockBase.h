// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockBase.generated.h"

UCLASS()
class MC_WORLDGENERATION_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBase();
	static int BlockDimension;

private:
	UPROPERTY(EditAnywhere)
	bool bDefaultDisable = false;
	UPROPERTY(EditAnywhere)
		bool bAlwaysDisableTick = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetActive(bool Active);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "BlockType.generated.h"

/**
 * 
 */
enum BlockType
{
	grass,
	soil,
	wood,
	leaf
};

UCLASS()
class MC_WORLDGENERATION_API UBlockType : public UUserDefinedEnum
{
	GENERATED_BODY()

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MC_WORLDGENERATION_API MyMathUtility
{
public:
	MyMathUtility();
	~MyMathUtility();

	static bool RandomWeightedBool(int percentage);
	static int AreaBoundedByTwoPoints(FVector2D minPtr, FVector2D maxPtr);
	static int DensityToCount(int density, int area, int densityDivisor);
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMathUtility.h"
#include "Math/UnrealMathUtility.h"

MyMathUtility::MyMathUtility()
{
}

MyMathUtility::~MyMathUtility()
{
}

bool MyMathUtility::RandomWeightedBool(int percentage)
{
	return percentage >= FMath::RandRange(0, 100);
}

int MyMathUtility::AreaBoundedByTwoPoints(FVector2D minPtr, FVector2D maxPtr)
{
	return FMath::Abs(minPtr.X - maxPtr.X) * FMath::Abs(minPtr.Y - maxPtr.Y);
}

int MyMathUtility::DensityToCount(int density, int area, int densityDivisor)
{
	return density * area / densityDivisor;
}


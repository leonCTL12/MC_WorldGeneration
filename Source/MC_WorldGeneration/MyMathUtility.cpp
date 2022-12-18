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
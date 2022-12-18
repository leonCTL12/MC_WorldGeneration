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
};

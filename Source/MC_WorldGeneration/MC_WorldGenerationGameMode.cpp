// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MC_WorldGenerationGameMode.h"
#include "MC_WorldGenerationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMC_WorldGenerationGameMode::AMC_WorldGenerationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

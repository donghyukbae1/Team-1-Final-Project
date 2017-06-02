// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PowerRun.h"
#include "PowerRunGameMode.h"
#include "PlayerRunner.h"

APowerRunGameMode::APowerRunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

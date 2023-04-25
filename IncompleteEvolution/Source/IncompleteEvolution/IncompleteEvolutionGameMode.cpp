// Copyright Epic Games, Inc. All Rights Reserved.

#include "IncompleteEvolutionGameMode.h"
#include "IncompleteEvolutionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIncompleteEvolutionGameMode::AIncompleteEvolutionGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

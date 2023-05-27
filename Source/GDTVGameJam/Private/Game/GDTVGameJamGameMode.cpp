// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/GDTVGameJamGameMode.h"
#include "Characters/GDTVGameJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGDTVGameJamGameMode::AGDTVGameJamGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}

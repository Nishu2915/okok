// Copyright Epic Games, Inc. All Rights Reserved.
#include "Characters/GDTVGameJamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"



AGDTVGameJamCharacter::AGDTVGameJamCharacter()
{

}

void AGDTVGameJamCharacter::SetDesiredMovement(bool NewOrientRotationToMovement, bool NewUseControllerRotationYaw)
{
	GetCharacterMovement()->bOrientRotationToMovement = NewOrientRotationToMovement;
	bUseControllerRotationYaw = NewUseControllerRotationYaw;
}



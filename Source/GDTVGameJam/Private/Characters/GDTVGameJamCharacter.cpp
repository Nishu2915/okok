// Copyright Epic Games, Inc. All Rights Reserved.
#include "Characters/GDTVGameJamCharacter.h"
#include "Components/GDTV_MotionWarpingComponent.h"
#include "Components/GDTV_StatusComponent.h"



AGDTVGameJamCharacter::AGDTVGameJamCharacter()
{
	GDTV_MotionWarping = CreateDefaultSubobject<UGDTV_MotionWarpingComponent>(TEXT("GDTV_MotionWarping"));
	GDTV_StatusComponent = CreateDefaultSubobject<UGDTV_StatusComponent>(TEXT("GDTV_StatusComponent"));

}

void AGDTVGameJamCharacter::GetHit_Implementation(AGDTVGameJamCharacter* Hitter, const FVector& ImpactPoint)
{
}

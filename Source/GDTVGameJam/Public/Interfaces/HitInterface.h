// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

class AGDTVGameJamCharacter;

class GDTVGAMEJAM_API IHitInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void GetHit(AGDTVGameJamCharacter* Hitter, const FVector& ImpactPoint);
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "GDTV_AIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, meta = (BlueprintSpawnableComponent), config = Game)
class GDTVGAMEJAM_API UGDTV_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure)
	UAISenseConfig_Sight* GetAISenseSight() const;

	UFUNCTION(BlueprintCallable)
	void SetSightRadius(UAISenseConfig_Sight* SightConfig, float SightRadius);

	UFUNCTION(BlueprintCallable)
	void SetLoseSightRadius(UAISenseConfig_Sight* SightConfig, float LoseSightRadius);
};

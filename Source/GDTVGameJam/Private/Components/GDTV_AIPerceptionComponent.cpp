// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GDTV_AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"

UAISenseConfig_Sight* UGDTV_AIPerceptionComponent::GetAISenseSight() const
{
	for (UAISenseConfig* Config : SensesConfig)
	{
		if (UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(Config))
		{
			return SightConfig;
		}
	}

	return nullptr;
}

void UGDTV_AIPerceptionComponent::SetSightRadius(UAISenseConfig_Sight* SightConfig, float SightRadius)
{
	if (!SightConfig) return;

	SightConfig->SightRadius = SightRadius;
}

void UGDTV_AIPerceptionComponent::SetLoseSightRadius(UAISenseConfig_Sight* SightConfig, float LoseSightRadius)
{
	if (!SightConfig) return;

	SightConfig->LoseSightRadius = LoseSightRadius;
}

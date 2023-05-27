// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionWarpingComponent.h"
#include "GDTV_MotionWarpingComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "Motion Warping", meta = (BlueprintSpawnableComponent), config = Game)
class GDTVGAMEJAM_API UGDTV_MotionWarpingComponent : public UMotionWarpingComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnyWhere, Category = Combat)
	double WarpTargetDistance = 75.f;

	UFUNCTION(BlueprintCallable)
	void UpdateTranslationAndRotationToTarget(AActor* WarpTarget, FName TranslationName, FName RotationName);
};

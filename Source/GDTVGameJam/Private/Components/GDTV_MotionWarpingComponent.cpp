// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GDTV_MotionWarpingComponent.h"

void UGDTV_MotionWarpingComponent::UpdateTranslationAndRotationToTarget(AActor* WarpTarget, FName TranslationName, FName RotationName)
{
    if (WarpTarget == nullptr) return;

    const FVector WarpTargetLocation = WarpTarget->GetActorLocation();
    const FVector Location = GetOwner()->GetActorLocation();

    FVector TargetToMe = (Location - WarpTargetLocation).GetSafeNormal();
    TargetToMe *= WarpTargetDistance;


    FVector TranslationTarget = WarpTargetLocation + TargetToMe;
    FVector RotationTarget = WarpTargetLocation;

    AddOrUpdateWarpTargetFromLocation(TranslationName, TranslationTarget);
    AddOrUpdateWarpTargetFromLocation(RotationName, RotationTarget);
}

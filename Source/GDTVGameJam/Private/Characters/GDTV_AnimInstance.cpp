// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GDTV_AnimInstance.h"
#include "Characters/GDTV_PlayerCharacter.h"
#include <Kismet/KismetMathLibrary.h>

void UGDTV_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);
    if (GDTV_Character == nullptr) {
        GDTV_Character = Cast<AGDTV_PlayerCharacter>(TryGetPawnOwner());
    }
    if (GDTV_Character == nullptr) return;

    TurningInPlace = GDTV_Character->GetTurningInPlace();
    //offset yaw for straffing
    FRotator AimRotation = GDTV_Character->GetBaseAimRotation();
    FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(GDTV_Character->GetVelocity());
    FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
    // 6.f lower smoother
    DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);// to make animation interp to the shortest path
    YawOffset = DeltaRotation.Yaw;

    CharacterRotationLastFrame = CharacterRotation;
    CharacterRotation = GDTV_Character->GetActorRotation();
    const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
    const float Target = Delta.Yaw / DeltaTime; // scale up

    AO_Yaw = GDTV_Character->GetAO_Yaw();
    AO_Pitch = GDTV_Character->GetAO_Pitch();
    bRotateRootBone = GDTV_Character->ShouldRotateRootBone();

}

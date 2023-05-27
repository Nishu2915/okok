// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GDTVGameJamCharacter.h"
#include "GDTV_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GDTVGAMEJAM_API UGDTV_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AGDTV_PlayerCharacter> GDTV_Character;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float YawOffset;
	FRotator CharacterRotationLastFrame;
	FRotator CharacterRotation;
	FRotator DeltaRotation;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float AO_Yaw;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float AO_Pitch;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ETurningInPlace TurningInPlace;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bUseAimOffsets;
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bRotateRootBone;
};

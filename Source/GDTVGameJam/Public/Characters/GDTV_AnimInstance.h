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

};

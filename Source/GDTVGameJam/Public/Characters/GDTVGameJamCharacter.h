// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GDTVGameJamCharacter.generated.h"


UENUM(BlueprintType)
enum class ETurningInPlace : uint8
{
	ETIP_Left UMETA(DisplayName = "Turning Left"),
	ETIP_Right UMETA(DisplayName = "Turning Right"),
	ETIP_NotTurning UMETA(DisplayName = "Not Turning"),

	ETIP_MAX UMETA(DisplayName = "DefaultMAX")
};

class UGDTV_MotionWarpingComponent;
class UGDTV_StatusComponent;

UCLASS(Abstract, config=Game)
class AGDTVGameJamCharacter : public ACharacter
{
	GENERATED_BODY()
private:

	
	
public:
	AGDTVGameJamCharacter();
	
	UFUNCTION(BlueprintCallable)
	void SetDesiredMovement(bool NewOrientRotationToMovement, bool NewUseControllerRotationYaw);

	UPROPERTY(BlueprintReadWrite)
	float Health = 100.f;
};


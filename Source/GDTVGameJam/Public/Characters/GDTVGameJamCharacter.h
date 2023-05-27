// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interfaces/HitInterface.h"
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
class AGDTVGameJamCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGDTV_MotionWarpingComponent> GDTV_MotionWarping;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGDTV_StatusComponent> GDTV_StatusComponent;


public:
	AGDTVGameJamCharacter();
	
	virtual void GetHit_Implementation(AGDTVGameJamCharacter* Hitter, const FVector& ImpactPoint) override;
};


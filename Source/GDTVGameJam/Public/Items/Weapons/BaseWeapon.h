// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseWeapon.generated.h"

class UGDTV_TraceComponent;

UCLASS(Blueprintable)
class GDTVGAMEJAM_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()
public:
	ABaseWeapon();
private:

protected:
	virtual void BeginPlay() override;
	virtual void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;



#pragma region Setter/Getter
public:
	

#pragma endregion
};

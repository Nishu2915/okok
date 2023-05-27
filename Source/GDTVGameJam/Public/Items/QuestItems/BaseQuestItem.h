// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseQuestItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GDTVGAMEJAM_API ABaseQuestItem : public ABaseItem
{
	GENERATED_BODY()
	
protected:
	virtual void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

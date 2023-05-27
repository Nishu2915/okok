// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"


class USphereComponent;
class USkeletalMeshComponent;

UCLASS(Abstract)
class GDTVGAMEJAM_API ABaseItem : public AActor
{
	GENERATED_BODY()

protected:
#pragma region Components

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> RootSceneComponent;

	/*if don't have to use trace component*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PickupMesh;

	/*required, if want to use trace component*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> PickupSKMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> PickupSphereComponent;
#pragma endregion


public:	
	// Sets default values for this actor's properties
	ABaseItem();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Pickup)
	float PickupRadius = 250.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	virtual void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

#pragma region Setter/Getter
public:
	UStaticMeshComponent* GetPickupMesh() const { return PickupMesh; }
	USkeletalMeshComponent* GetPickupSKMesh() const { return PickupSKMesh; }

#pragma endregion

};

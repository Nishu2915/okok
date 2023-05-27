// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Pickup UMETA(DisplayName = "Pickup"),
	EWS_Unequipped UMETA(DisplayName = "Unequipped"),
	EWS_Equipped UMETA(DisplayName = "Equipped")

};

class UGDTV_TraceComponent;

UCLASS(Blueprintable)
class GDTVGAMEJAM_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()
public:
	ABaseWeapon();
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGDTV_TraceComponent> TraceComponent;

protected:
	virtual void BeginPlay() override;
	virtual void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	EWeaponState CurrentState = EWeaponState::EWS_Pickup;

#pragma region Setter/Getter
public:
	void SetWeaponState(EWeaponState NewState);
	EWeaponState GetWeaponState() const { return CurrentState; }

#pragma endregion
};

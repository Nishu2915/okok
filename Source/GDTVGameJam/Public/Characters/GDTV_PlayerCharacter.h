// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDTVGameJamCharacter.h"
#include "GDTV_PlayerCharacter.generated.h"


UENUM(BlueprintType)
enum class EMovementSpeedMode : uint8
{
	Crouch UMETA(DisplayName = "Crouch"),
	Walk UMETA(DisplayName = "Walk"),
	Sprint UMETA(DisplayName = "Sprint")
};

class ABaseWeapon;

UCLASS(Blueprintable)
class GDTVGAMEJAM_API AGDTV_PlayerCharacter : public AGDTVGameJamCharacter
{
	GENERATED_BODY()

public:
	AGDTV_PlayerCharacter();

#pragma region Components
private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGDTV_MotionWarpingComponent> GDTV_MotionWarping;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
#pragma endregion

#pragma region Input Maps
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Equip Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	/** Action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BlockAction;
#pragma endregion

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseWeapon> CurrentWeapon = nullptr;

#pragma region TurnInplace
	bool bRotateRootBone;
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	void TurnInplace(float DeltaTime);
	void RotateInPlace(float DeltaTime);
	void AimOffset(float DeltaTime);
	void CalculateAO_Pitch();
	float CalculateSpeed();

#pragma endregion

	uint8 bEquipped : 1;
	uint8 bEquipping : 1;

protected:
#pragma region Input Funcs

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for crouching input */
	void ToggleCrouch(const FInputActionValue& Value);

	/** Called for un/equip input */
	void ToggleEquip(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnSprintPressed(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent)
	void OnSprintReleased(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent)
	void SetMovementMode(EMovementSpeedMode Mode);
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttackPressed(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent)
	void OnBlockPressed(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent)
	void OnBlockReleased(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Combat)
	FName WeaponSocketName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Combat)
	FName BackSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Combat)
	TObjectPtr<UAnimMontage> EquipMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Combat)
	TObjectPtr<UAnimMontage> UnequipMontage;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(ABaseWeapon* Weapon);
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon();

#pragma region Getter
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEquipped() const { return bEquipped; }

#pragma endregion
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GDTV_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/Weapons/BaseWeapon.h"
#include <Kismet/KismetMathLibrary.h>
#include "Components/GDTV_MotionWarpingComponent.h"

AGDTV_PlayerCharacter::AGDTV_PlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	bEquipped = false;
	bEquipping = false;

	GDTV_MotionWarping = CreateDefaultSubobject<UGDTV_MotionWarpingComponent>(TEXT("GDTV_MotionWarping"));

	
}

void AGDTV_PlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AGDTV_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateInPlace(DeltaTime);
}


#pragma region Weapon
void AGDTV_PlayerCharacter::EquipWeapon(ABaseWeapon* Weapon)
{
	if (Weapon)
	{
		if (CurrentWeapon && Weapon != CurrentWeapon)
		{
			CurrentWeapon->Destroy();
		}

		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->GetPickupSKMesh()->AttachToComponent(GetMesh(), TransformRules, WeaponSocketName);
		Weapon->SetOwner(this);
		CurrentWeapon = Weapon;
		bEquipped = true;
		bEquipping = false;
	}
}

void AGDTV_PlayerCharacter::UnequipWeapon()
{
	if (!CurrentWeapon) return;

	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	CurrentWeapon->GetPickupSKMesh()->AttachToComponent(GetMesh(), TransformRules, BackSocketName);
	bEquipped = false;
	bEquipping = false;

}
#pragma endregion

#pragma region Movement
void AGDTV_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGDTV_PlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGDTV_PlayerCharacter::Look);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AGDTV_PlayerCharacter::ToggleCrouch);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AGDTV_PlayerCharacter::ToggleEquip);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AGDTV_PlayerCharacter::OnSprintPressed);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AGDTV_PlayerCharacter::OnSprintReleased);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGDTV_PlayerCharacter::OnAttackPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGDTV_PlayerCharacter::OnBlockPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AGDTV_PlayerCharacter::OnBlockReleased);
	}

}

void AGDTV_PlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGDTV_PlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGDTV_PlayerCharacter::ToggleCrouch(const FInputActionValue& Value)
{
	if (bEquipped || bEquipping) return;

	if (bIsCrouched)
	{
		UnCrouch();
		SetMovementMode(EMovementSpeedMode::Walk);
	}
	else
	{
		Crouch();
		SetMovementMode(EMovementSpeedMode::Crouch);
	}
}

void AGDTV_PlayerCharacter::ToggleEquip(const FInputActionValue& Value)
{
	if (!CurrentWeapon || !CurrentWeapon->GetPickupSKMesh()->IsVisible() || bIsCrouched || bEquipping) return;

	bEquipping = true;

	if (bEquipped)
	{
		PlayAnimMontage(UnequipMontage);
		//UnequipWeapon();
	}
	else
	{
		//EquipWeapon(CurrentWeapon);
		PlayAnimMontage(EquipMontage);

	}
}

#pragma endregion

#pragma region TurnInplace

void AGDTV_PlayerCharacter::RotateInPlace(float DeltaTime)
{
	AimOffset(DeltaTime);
	CalculateAO_Pitch();
}

float AGDTV_PlayerCharacter::CalculateSpeed()
{
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	return Velocity.Size();
}

void AGDTV_PlayerCharacter::AimOffset(float DeltaTime)
{

	float Speed = CalculateSpeed();
	bool bIsInAir = GetCharacterMovement()->IsFalling();


	if (Speed == 0.f && !bIsInAir) //standing still and not jumping
	{
		bRotateRootBone = true;
		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		AO_Yaw = DeltaAimRotation.Yaw;
		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		bUseControllerRotationYaw = true;
		TurnInplace(DeltaTime);
	}
	if (Speed > 0.f || bIsInAir) // running or jumping
	{
		bRotateRootBone = false;
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f); // pitch yaw roll
		AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	}

	CalculateAO_Pitch();
}

void AGDTV_PlayerCharacter::TurnInplace(float DeltaTime)
{
	if (AO_Yaw > 90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
	}
	else if (AO_Yaw < -90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
	}
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			// after turn 15 degree reset the aim rotation.
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

void AGDTV_PlayerCharacter::CalculateAO_Pitch()
{
	AO_Pitch = GetBaseAimRotation().Pitch;
	if (AO_Pitch > 90.f)
	{
		// snatched from stephen lol
		// have to do this cuz it was compressed(has no negative value) to send over the internet
		// map pitch from range [270,360) to the range [-90, 0)
		FVector2D InRange(270.f, 360.f);
		FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
}
#pragma endregion


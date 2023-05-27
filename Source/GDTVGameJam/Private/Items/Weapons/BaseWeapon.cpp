// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Components/GDTV_TraceComponent.h"
#include "Characters/GDTV_PlayerCharacter.h"

ABaseWeapon::ABaseWeapon()
{
	TraceComponent = CreateDefaultSubobject<UGDTV_TraceComponent>(TEXT("TraceComponent"));
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	TraceComponent->Init(PickupSKMesh);
}

void ABaseWeapon::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Yes"));
	if (AGDTV_PlayerCharacter* Player = Cast<AGDTV_PlayerCharacter>(OtherActor))
	{
		Player->EquipWeapon(this);
	}
}

void ABaseWeapon::SetWeaponState(EWeaponState NewState)
{
	switch (NewState)
	{
	case EWeaponState::EWS_Pickup:
		break;
	case EWeaponState::EWS_Unequipped:
		break;
	case EWeaponState::EWS_Equipped:
		break;
	default:
		break;
	}
}

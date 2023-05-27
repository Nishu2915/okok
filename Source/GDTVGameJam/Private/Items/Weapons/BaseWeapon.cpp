// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Characters/GDTV_PlayerCharacter.h"
#include "Components/SphereComponent.h"

ABaseWeapon::ABaseWeapon()
{
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AGDTV_PlayerCharacter* Player = Cast<AGDTV_PlayerCharacter>(OtherActor))
	{
		Player->EquipWeapon(this);
		Player->UnCrouch();
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		GetRootComponent()->AttachToComponent(Player->GetRootComponent(), TransformRules);
		PickupSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


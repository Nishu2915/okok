// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMeshComponent"));
	PickupMesh->SetupAttachment(RootSceneComponent);
	PickupSKMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PickupSKMeshComponent"));
	PickupSKMesh->SetupAttachment(RootSceneComponent);
	PickupSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphereComponent"));
	PickupSphereComponent->SetupAttachment(RootSceneComponent);

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Bind"));
	PickupSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnItemBeginOverlap);
	
}

void ABaseItem::OnConstruction(const FTransform& Transform)
{
	PickupSphereComponent->SetSphereRadius(PickupRadius);
}

void ABaseItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Parent"));

}



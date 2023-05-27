// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GDTV_TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"

static	TAutoConsoleVariable<int32> CVarShowTrace(
	TEXT("GDTV.ShowTrace"),
	0,
	TEXT("Draw debug info about Trace")
	TEXT(" 0: off/n")
	TEXT(" 1: on/n"),
	ECVF_Cheat
);

// Sets default values for this component's properties
UGDTV_TraceComponent::UGDTV_TraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}


void UGDTV_TraceComponent::ClearIgnoredActors()
{
	IgnoredActors.Empty();
}

void UGDTV_TraceComponent::Init(USkeletalMeshComponent* InSKM)
{
	if (InSKM)
	{
		SKM = InSKM;
		SetSocketsLoc();
	}
	
	IgnoredActors.Empty();
	GetWorld()->GetTimerManager().SetTimer(TraceTick_TimerHandle, this, &UGDTV_TraceComponent::Trace, TickRate, true);


	
}

void UGDTV_TraceComponent::SetSocketsLoc()
{
	SocketStartLoc = SKM->GetSocketLocation(TraceStartSocket);
	SocketEndLoc = SKM->GetSocketLocation(TraceEndSocket);
}

void UGDTV_TraceComponent::Trace()
{
	SetSocketsLoc();

	int32 bDebug = CVarShowTrace.GetValueOnAnyThread();
	if (bDebug)
	{
		DrawDebugSphere(GetWorld(), SocketStartLoc, 12.f, 12, FColor::Yellow, false, .3f);
		DrawDebugSphere(GetWorld(), SocketEndLoc, 12.f, 12, FColor::Yellow, false, .3f);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Start %f, %f, %f"), SocketStartLoc.X, SocketStartLoc.Y, SocketStartLoc.Z);
		UE_LOG(LogTemp, Warning, TEXT("End %f, %f, %f"), SocketStartLoc.X, SocketStartLoc.Y, SocketStartLoc.Z);
	}

	FHitResult HitResult;

	bool bBlocked = UKismetSystemLibrary::CapsuleTraceSingle(this, SocketStartLoc, SocketEndLoc, TraceRadius, TraceHalfHeight,
		ETraceTypeQuery::TraceTypeQuery1, true, IgnoredActors, bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResult, true);

	if(bBlocked)
	{
		//TODO: Do some damage
	}

}


void UGDTV_TraceComponent::TraceActivate()
{
}

void UGDTV_TraceComponent::TraceDeactivate()
{
}
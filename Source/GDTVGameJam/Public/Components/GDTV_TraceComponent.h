// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GDTV_TraceComponent.generated.h"

class USkeletalMeshComponent;

/*A trace component from socket to socket, only Skeletal Component can use this*/
UCLASS( ClassGroup=(Trace), meta=(BlueprintSpawnableComponent) )
class GDTVGAMEJAM_API UGDTV_TraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGDTV_TraceComponent();
	void Init(USkeletalMeshComponent* InSKM);
	
	UPROPERTY(EditDefaultsOnly, Category = Trace)
	float TickRate = .1f;
	UPROPERTY(EditDefaultsOnly, Category = Trace)
	int32 TraceRadius = 30.f;
	UPROPERTY(EditDefaultsOnly, Category = Trace)
	int32 TraceHalfHeight = 60.f;

private:
	void SetSocketsLoc();
	UPROPERTY(Transient, EditDefaultsOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	FName TraceStartSocket;

	UPROPERTY(Transient, EditDefaultsOnly, Category = Trace, meta = (AllowPrivateAccess = "true"))
	FName TraceEndSocket;

	UPROPERTY(Transient)
	TArray<AActor*> IgnoredActors;

	FTimerHandle TraceTick_TimerHandle;

	UFUNCTION()
	void Trace();

	FVector SocketStartLoc{ 0.f };
	FVector SocketEndLoc{ 0.f };
	
	UPROPERTY(Transient)
	TObjectPtr<USkeletalMeshComponent> SKM;
public:

	UFUNCTION(BlueprintCallable)
		void ClearIgnoredActors();

	UFUNCTION(BlueprintCallable)
		void TraceActivate();

	UFUNCTION(BlueprintCallable)
		void TraceDeactivate();

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GDTV_GameInstance.generated.h"


/** Delegate called when the save game has been loaded/reset */
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoaded, URPGSaveGame*, SaveGame);
//DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedNative, URPGSaveGame*);
/**
 * 
 */
UCLASS()
class GDTVGAMEJAM_API UGDTV_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

};

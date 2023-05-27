// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GDTV_BPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GDTVGAMEJAM_API UGDTV_BPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Show the native loading screen, such as on a map transfer. If bPlayUntilStopped is false, it will be displayed for PlayTime and automatically stop */
	UFUNCTION(BlueprintCallable, Category = Loading)
	static void PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime);

	/** Turns off the native loading screen if it is visible. This must be called if bPlayUntilStopped was true */
	UFUNCTION(BlueprintCallable, Category = Loading)
	static void StopLoadingScreen();
	
	/** Returns true if this is being run from an editor preview */
	UFUNCTION(BlueprintPure, Category = Loading)
	static bool IsInEditor();

	//Returns the project version set in the 'Project Settings' > 'Description' section of the editor
	UFUNCTION(BlueprintPure, Category = "Project")
	static FString GetProjectVersion();
};

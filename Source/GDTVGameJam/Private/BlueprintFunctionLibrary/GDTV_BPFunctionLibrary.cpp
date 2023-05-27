// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctionLibrary/GDTV_BPFunctionLibrary.h"
//#include "Modules/ModuleManager.h"
#include "LoadingScreen.h"

void UGDTV_BPFunctionLibrary::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	//this way link error? so we do interface
	//FLoadingScreenModule& LoadingScreenModule = FModuleManager::LoadModuleChecked<FLoadingScreenModule>(TEXT("LoadingScreen")); //
	ILoadingScreenModule& LoadingScreenModule = ILoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void UGDTV_BPFunctionLibrary::StopLoadingScreen()
{
	//FLoadingScreenModule& LoadingScreenModule = FModuleManager::LoadModuleChecked<FLoadingScreenModule>(TEXT("LoadingScreen"));
	ILoadingScreenModule& LoadingScreenModule = ILoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

bool UGDTV_BPFunctionLibrary::IsInEditor()
{
	return GIsEditor;
}

FString UGDTV_BPFunctionLibrary::GetProjectVersion()
{
	FString ProjectVersion;

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);

	return ProjectVersion;
}

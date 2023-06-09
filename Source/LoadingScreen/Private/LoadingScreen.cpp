#include "LoadingScreen.h"
#include "Modules/ModuleManager.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"

//#define LoadingScreenImage1 TEXT("/Game/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo")

#pragma region Slate

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!
struct FLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};

class SLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		// Load version of the logo with text baked in, path is hardcoded because this loads very early in startup
		//static const FName LoadingScreenName(LoadingScreenImage1);

		//LoadingScreenBrush = MakeShareable(new FLoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256)));

		FSlateBrush* BGBrush = new FSlateBrush();
		//BGBrush->TintColor = FLinearColor(0.034f, 0.034f, 0.034f, 1.0f);
		BGBrush->TintColor = FLinearColor(0.f, 0.f, 0.f, 1.0f);

		ChildSlot
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(BGBrush)
			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(/*LoadingScreenBrush.Get()*/new FSlateBrush())
				.ColorAndOpacity(FColor::White)
			]
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.HAlign(HAlign_Right)
			.Padding(FMargin(10.0f))
			[
				SNew(SThrobber)
				.Visibility(this, &SLoadingScreen::GetLoadIndicatorVisibility)
			]
			]
			];
	}

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		bool Vis = GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

	/** Loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

#pragma endregion


//void FLoadingScreenModule::StartupModule()
//{
//	// Force load for cooker reference
//	LoadObject<UObject>(nullptr, LoadingScreenImage1);
//
//	if (IsMoviePlayerEnabled())
//	{
//		CreateScreen();
//	}
//}
//
//void FLoadingScreenModule::StopInGameLoadingScreen()
//{
//	GetMoviePlayer()->StopMovie();
//}
//
//void FLoadingScreenModule::CreateScreen()
//{
//	FLoadingScreenAttributes LoadingScreen;
//	LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
//	LoadingScreen.MinimumLoadingScreenDisplayTime = 3.f;
//	LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
//}

class FLoadingScreenModule : public ILoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// Force load for cooker reference
		//LoadObject<UObject>(nullptr, LoadingScreenImage1);

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreen.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreen.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		UE_LOG(LogTemp, Warning, TEXT("StartLoadingScreen C++"));
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

};


IMPLEMENT_GAME_MODULE(FLoadingScreenModule, LoadingScreen);
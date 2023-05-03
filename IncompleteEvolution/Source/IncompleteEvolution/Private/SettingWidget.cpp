// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingWidget.h"
#include "GameFramework/GameUserSettings.h"

void USettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FullScreenMode = GEngine->GetGameUserSettings()->GetFullscreenMode();
	ResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	DesktopResolutionNumber = GEngine->GetGameUserSettings()->GetDesktopResolution();
	
	if(!ResolutionButton->OnClicked.IsBound())
	{
		ResolutionButton->OnClicked.AddDynamic(this,&USettingWidget::ResolutionButtonOnClick);
	}
	if(FullScreenMode==2)
	{
		if(ResolutionNumber.X == 1920&&ResolutionNumber.Y== 1080)
		{
			CurrentResolution->SetText(FText::FromString("1920x1080"));
		}
		else if(ResolutionNumber.X==2560&&ResolutionNumber.Y== 1440)
		{
			CurrentResolution->SetText(FText::FromString("2560x1440"));
		}
		else if(ResolutionNumber.X==2560&&ResolutionNumber.Y== 1600)
		{
			CurrentResolution->SetText(FText::FromString("2560x1600"));
		}
	}
	else
	{
		CurrentResolution->SetText(FText::FromString("Can not change"));
	}
	
	if(!ScreenModeButton->OnClicked.IsBound())
	{
		ScreenModeButton->OnClicked.AddDynamic(this,&USettingWidget::USettingWidget::ScreenModeButtonOnClick);
	}
	
	if(FullScreenMode==0)
	{
		CurrentScreenMode->SetText(FText::FromString("Full Screen"));
	}
	else if(FullScreenMode==1)
	{
		CurrentScreenMode->SetText(FText::FromString("Windowed Full screen"));
	}
	else if(FullScreenMode==2)
	{
		CurrentScreenMode->SetText(FText::FromString("Windowed"));
	}
}

void USettingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Current Resolution: %d %d"), ResolutionNumber.X, ResolutionNumber.Y);
	//UE_LOG(LogTemp, Warning, TEXT("Current Mode: %d"),FullScreenMode);
	
}

void USettingWidget::ResolutionButtonOnClick()
{
	if(FullScreenMode==2)
	{
		if(ResolutionNumber.X == 1920&&ResolutionNumber.Y== 1080)
		{
			CurrentResolution->SetText(FText::FromString("2560x1440"));
			GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
			GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(2560, 1440));
			GEngine->GetGameUserSettings()->ApplySettings(true);
		}
		else if(ResolutionNumber.X==2560&&ResolutionNumber.Y== 1440)
		{
			CurrentResolution->SetText(FText::FromString("2560x1600"));
			GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
			GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(2560, 1600));
			GEngine->GetGameUserSettings()->ApplySettings(true);
		}
		else if(ResolutionNumber.X==2560&&ResolutionNumber.Y== 1600)
		{
			CurrentResolution->SetText(FText::FromString("1920x1080"));
			GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
			GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1920, 1080));
			GEngine->GetGameUserSettings()->ApplySettings(true);
		}
	}
	ResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	FullScreenMode = GEngine->GetGameUserSettings()->GetFullscreenMode();
	DesktopResolutionNumber = GEngine->GetGameUserSettings()->GetDesktopResolution();
}

void USettingWidget::ScreenModeButtonOnClick()
{
	if(FullScreenMode==0)
	{
		CurrentScreenMode->SetText(FText::FromString("Windowed Full screen"));
		GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		GEngine->GetGameUserSettings()->ApplySettings(true);
	}
	else if(FullScreenMode==1)
	{
		CurrentScreenMode->SetText(FText::FromString("Windowed"));
		GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
		GEngine->GetGameUserSettings()->SetScreenResolution(DesktopResolutionNumber);
		if(ResolutionNumber.X == 1920&&ResolutionNumber.Y== 1080)
		{
				

		}
		else if(ResolutionNumber.X==2560&&ResolutionNumber.Y== 1440)
		{
			CurrentResolution->SetText(FText::FromString("2560x1440"));
		}
		else if(ResolutionNumber.X==2560&&ResolutionNumber.Y== 1600)
		{
			CurrentResolution->SetText(FText::FromString("2560x1600"));
		}
		GEngine->GetGameUserSettings()->ApplySettings(true);
	}
	else if(FullScreenMode==2)
	{
		CurrentScreenMode->SetText(FText::FromString("Full screen"));
		CurrentResolution->SetText(FText::FromString("Can not Change"));
		GEngine->GetGameUserSettings()->SetScreenResolution(DesktopResolutionNumber);
		GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen);
		GEngine->GetGameUserSettings()->ApplySettings(true);
	}
	ResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	FullScreenMode = GEngine->GetGameUserSettings()->GetFullscreenMode();
	DesktopResolutionNumber = GEngine->GetGameUserSettings()->GetDesktopResolution();
}


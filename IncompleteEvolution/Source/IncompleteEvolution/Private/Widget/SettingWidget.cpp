// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SettingWidget.h"
#include "GameFramework/GameUserSettings.h"

void USettingWidget::SM_SelectedButtonOnClick()
{
	SM_OptionsButton->SetVisibility(ESlateVisibility::Visible);
}

void USettingWidget::SM_OptionsButtonOnUnhovered()
{
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::FullScreenOnClick()
{
	SM_SelectedText->SetText(FText::FromString("Full Screen"));
	RE_SelectedText->SetText(FText::FromString("Disabled"));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	GEngine->GetGameUserSettings()->SetScreenResolution(DesktopResolutionNumber);
	GEngine->GetGameUserSettings()->ApplySettings(true);
	CurrentScreenMode = GEngine->GetGameUserSettings()->GetFullscreenMode();
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::WindowedOnClick()
{
	SM_SelectedText->SetText(FText::FromString("Windowed"));
	RE_SelectedText->SetText(FText::FromString("1920x1080"));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1920, 1080));
	GEngine->GetGameUserSettings()->ApplySettings(true);
	CurrentScreenMode = GEngine->GetGameUserSettings()->GetFullscreenMode();
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::RE_SelectedButtonOnClick()
{
	if(CurrentScreenMode==2)
	{
		RE_OptionsButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void USettingWidget::RE_OptionsButtonOnUnhovered()
{
	if(CurrentScreenMode==2)
	{
		RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USettingWidget::FhdOnClick()
{
	RE_SelectedText->SetText(FText::FromString("1920x1080"));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(1920, 1080));
	GEngine->GetGameUserSettings()->ApplySettings(true);
	CurrentResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::Qhd1OnClick()
{
	RE_SelectedText->SetText(FText::FromString("2560x1440"));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(2560, 1440));
	GEngine->GetGameUserSettings()->ApplySettings(true);
	CurrentResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::Qhd2OnClick()
{
	RE_SelectedText->SetText(FText::FromString("2560x1600"));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(2560, 1600));
	GEngine->GetGameUserSettings()->ApplySettings(true);
	CurrentResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::UhdOnClick()
{
	RE_SelectedText->SetText(FText::FromString("3840x2160"));
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(3840, 2160));
	GEngine->GetGameUserSettings()->ApplySettings(true);
	CurrentResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	SM_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
	RE_OptionsButton->SetVisibility(ESlateVisibility::Hidden);
}

void USettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	DesktopResolutionNumber = GEngine->GetGameUserSettings()->GetDesktopResolution();
	CurrentScreenMode = GEngine->GetGameUserSettings()->GetFullscreenMode();
	CurrentResolutionNumber = GEngine->GetGameUserSettings()->GetScreenResolution();
	
	FullScreenText->SetText(FText::FromString("Full Screen"));
	WindowedText->SetText(FText::FromString("Windowed"));

	if(!SM_SelectedButton->OnClicked.IsBound())
	{
		SM_SelectedButton->
		OnClicked.AddDynamic(this,&USettingWidget::SM_SelectedButtonOnClick);
	}
	if(!SM_OptionsButton->OnUnhovered.IsBound())
	{
		SM_OptionsButton->
		OnUnhovered.AddDynamic(this,&USettingWidget::SM_OptionsButtonOnUnhovered);
	}
	if(!FullScreen->OnClicked.IsBound())
	{
		FullScreen->
		OnClicked.AddDynamic(this,&USettingWidget::FullScreenOnClick);
	}
	if(!Windowed->OnClicked.IsBound())
	{
		Windowed->
		OnClicked.AddDynamic(this,&USettingWidget::WindowedOnClick);
	}
	if(!RE_SelectedButton->OnClicked.IsBound())
	{
		RE_SelectedButton->
		OnClicked.AddDynamic(this,&USettingWidget::RE_SelectedButtonOnClick);
	}
	if(!RE_OptionsButton->OnUnhovered.IsBound())
	{
		RE_OptionsButton->
		OnUnhovered.AddDynamic(this,&USettingWidget::RE_OptionsButtonOnUnhovered);
	}
	if(!FhdButton->OnClicked.IsBound())
	{
		FhdButton->
		OnClicked.AddDynamic(this,&USettingWidget::USettingWidget::FhdOnClick);
	}
	if(!Qhd1Button->OnClicked.IsBound())
	{
		Qhd1Button->
		OnClicked.AddDynamic(this,&USettingWidget::USettingWidget::Qhd1OnClick);
	}
	if(!Qhd2Button->OnClicked.IsBound())
	{
		Qhd2Button->
		OnClicked.AddDynamic(this,&USettingWidget::USettingWidget::Qhd2OnClick);
	}
	if(!UhdButton->OnClicked.IsBound())
	{
		UhdButton->
		OnClicked.AddDynamic(this,&USettingWidget::USettingWidget::UhdOnClick);
	}
	
	if(CurrentScreenMode == 1||CurrentScreenMode==0)
	{
		SM_SelectedText->SetText(FText::FromString("Full Screen"));
		RE_SelectedText->SetText(FText::FromString("Disabled"));
	}
	else if(CurrentScreenMode == 2)
	{
		SM_SelectedText->SetText(FText::FromString("Windowed"));
		if(CurrentResolutionNumber.X==1920&&CurrentResolutionNumber.Y==1080)
		{
			RE_SelectedText->SetText(FText::FromString("1920x1080"));
		}
		else if(CurrentResolutionNumber.X==2560&&CurrentResolutionNumber.Y==1440)
		{
			RE_SelectedText->SetText(FText::FromString("2560x1440"));
		}
		else if(CurrentResolutionNumber.X==2560&&CurrentResolutionNumber.Y==1600)
		{
			RE_SelectedText->SetText(FText::FromString("2560x1600"));
		}
		else if(CurrentResolutionNumber.X==3840&&CurrentResolutionNumber.Y==2160)
		{
			RE_SelectedText->SetText(FText::FromString("3840x2160"));
		}
	}
	
}

void USettingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


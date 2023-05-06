// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "SettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class INCOMPLETEEVOLUTION_API USettingWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	//FIntPoint ResolutionNumber;
	/*
	UPROPERTY(meta = (BindWidget))
	class UButton* ResolutionButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentResolution;
	
	UFUNCTION()
	void ResolutionButtonOnClick();

	int FullScreenMode;
	UPROPERTY(meta = (BindWidget))
	class UButton* ScreenModeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentScreenMode;
	
	UFUNCTION()
	void ScreenModeButtonOnClick();
	
	*/
	// Screen Mode Component
	int CurrentScreenMode;
	FIntPoint DesktopResolutionNumber;
	UPROPERTY(meta = (BindWidget))
	class UButton* SM_SelectedButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SM_SelectedText;
	UFUNCTION()
	void SM_SelectedButtonOnClick();

	UPROPERTY(meta = (BindWidget))
	class UButton* SM_OptionsButton;
	UFUNCTION()
	void SM_OptionsButtonOnUnhovered();

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* SM_OptionsBox;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* FullScreen;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FullScreenText;
	UFUNCTION()
	void FullScreenOnClick();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Windowed;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WindowedText;
	UFUNCTION()
	void WindowedOnClick();

	// Resolution Component
	FIntPoint CurrentResolutionNumber;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* RE_SelectedButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RE_SelectedText;
	UFUNCTION()
	void RE_SelectedButtonOnClick();

	UPROPERTY(meta = (BindWidget))
	class UButton* RE_OptionsButton;
	UFUNCTION()
	void RE_OptionsButtonOnUnhovered();

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* RE_OptionsBox;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* FhdButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FhdText;
	UFUNCTION()
	void FhdOnClick();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Qhd1Button;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Qhd1Text;
	UFUNCTION()
	void Qhd1OnClick();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Qhd2Button;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Qhd2Text;
	UFUNCTION()
	void Qhd2OnClick();

	UPROPERTY(meta = (BindWidget))
	class UButton* UhdButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UhdText;
	UFUNCTION()
	void UhdOnClick();
	
	virtual void NativeConstruct () override;
	virtual void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;

	
};

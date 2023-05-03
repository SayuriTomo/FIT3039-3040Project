// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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
	FIntPoint ResolutionNumber;
	
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
	
	FIntPoint DesktopResolutionNumber;
	
	
	virtual void NativeConstruct () override;
	virtual void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;

	
};

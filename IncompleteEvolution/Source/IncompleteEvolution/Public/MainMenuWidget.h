// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "GameFramework/GameUserSettings.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class INCOMPLETEEVOLUTION_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct () override;
	virtual void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;
};

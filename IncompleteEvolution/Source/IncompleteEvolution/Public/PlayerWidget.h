// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class INCOMPLETEEVOLUTION_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* OriginalCrossHair;

	UPROPERTY(meta = (BindWidget))
	class UImage* AimingCrossHair;
	
	AIncompleteEvolutionCharacter* Player;
	virtual void NativeConstruct () override;
	virtual void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;
};

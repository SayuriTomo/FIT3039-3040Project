// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class INCOMPLETEEVOLUTION_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UImage* OriginalCrossHair;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UImage* DarkImage;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UImage* AimingCrossHair;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UImage* DialogLine;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* EndText;
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* InteractHint;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* InteractCharacter;
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* InteractMessage;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* TaskMessage;

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* TaskBar;
	
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UTextBlock* ConversationHint;
	
	UPROPERTY(BlueprintReadWrite)
	AIncompleteEvolutionCharacter* Player;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Interacting;
	
	virtual void NativeConstruct () override;
	virtual void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

#include "Components/Image.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(Player)
	{
		
		if(Player->WhetherGrab)
		{
			OriginalCrossHair->SetVisibility(ESlateVisibility::Hidden);
			AimingCrossHair->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if(Player->AimGrab)
			{
				OriginalCrossHair->SetVisibility(ESlateVisibility::Hidden);
				AimingCrossHair->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				OriginalCrossHair->SetVisibility(ESlateVisibility::Visible);
				AimingCrossHair->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

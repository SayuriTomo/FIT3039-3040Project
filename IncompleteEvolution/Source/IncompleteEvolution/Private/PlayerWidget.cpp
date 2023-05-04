// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

#include "Components/Image.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	InteractHint->SetText(FText::FromString("Press F To Interact"));

	
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

		if(Player->AimInteract)
		{
			InteractHint->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			InteractHint->SetVisibility(ESlateVisibility::Hidden);
		}

		if(Player->Interacting)
		{
			if(CurrentTime<TimeLimit)
			{
				InteractMessage->SetText(FText::FromString(Player->InteractText));
				InteractMessage->SetVisibility(ESlateVisibility::Visible);
				CurrentTime += InDeltaTime;
			}
			else
			{
				Player->Interacting = false;
				CurrentTime = 0;
			}
		}
		else
		{
			InteractMessage->SetVisibility(ESlateVisibility::Hidden);
		}

		if(Player->TargetUpdate)
		{
			TaskMessage->SetText(FText::FromString(Player->TaskText));
			Player->TargetUpdate=false;
		}
	}
}

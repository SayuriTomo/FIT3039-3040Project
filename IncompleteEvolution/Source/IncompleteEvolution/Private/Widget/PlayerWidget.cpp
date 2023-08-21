// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerWidget.h"

#include "Components/Image.h"


void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	InteractHint->SetText(FText::FromString("[F] Interact"));
	DarkImage->SetVisibility(ESlateVisibility::Hidden);
	EndText->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(Player)
	{
		Interacting = Player->Interacting;
		if(Player->bIsStart)
		{
			DarkImage->SetVisibility(ESlateVisibility::Visible);
			OriginalCrossHair->SetVisibility(ESlateVisibility::Hidden);
			AimingCrossHair->SetVisibility(ESlateVisibility::Hidden);
			TaskMessage->SetVisibility(ESlateVisibility::Hidden);
			TaskBar->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			DarkImage->SetVisibility(ESlateVisibility::Hidden);
			OriginalCrossHair->SetVisibility(ESlateVisibility::Visible);
			AimingCrossHair->SetVisibility(ESlateVisibility::Visible);
			TaskMessage->SetVisibility(ESlateVisibility::Visible);
			TaskBar->SetVisibility(ESlateVisibility::Visible);
		}
		
		if(Player->bIsEnd)
		{
			DarkImage->SetVisibility(ESlateVisibility::Visible);
			EndText->SetVisibility(ESlateVisibility::Visible);
			TaskMessage->SetVisibility(ESlateVisibility::Hidden);
			TaskBar->SetVisibility(ESlateVisibility::Hidden);
			DialogLine->SetVisibility(ESlateVisibility::Hidden);
			DialogBlock->SetVisibility(ESlateVisibility::Hidden);
			OriginalCrossHair->SetVisibility(ESlateVisibility::Hidden);
			AimingCrossHair->SetVisibility(ESlateVisibility::Hidden);
		}
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
			if(Player->InteractText!="")
			{
				InteractMessage->SetText(FText::FromString(Player->InteractText));
				InteractMessage->SetVisibility(ESlateVisibility::Visible);
				
				InteractCharacter->SetText(FText::FromString(Player->InteractCharacterName));
				InteractCharacter->SetVisibility(ESlateVisibility::Visible);

				DialogLine->SetVisibility(ESlateVisibility::Visible);
				DialogBlock->SetVisibility(ESlateVisibility::Visible);
				
				ConversationHint->SetVisibility(ESlateVisibility::Visible);
			}
			
		}
		else
		{
			Player->Interacting = false;
			Player->InteractText = nullptr;
			Player->InteractCharacterName = nullptr;
			InteractMessage->SetVisibility(ESlateVisibility::Hidden);
			
			DialogLine->SetVisibility(ESlateVisibility::Hidden);
			DialogBlock->SetVisibility(ESlateVisibility::Hidden);
			
			InteractCharacter->SetVisibility(ESlateVisibility::Hidden);
			
			ConversationHint->SetVisibility(ESlateVisibility::Hidden);
			
		}

		if(Player->TargetUpdate)
		{
			TaskMessage->SetText(FText::FromString(Player->TaskText));
			Player->TargetUpdate=false;
			Player->TaskText = nullptr;
		}
	}
}
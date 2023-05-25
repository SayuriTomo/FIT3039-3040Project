// Fill out your copyright notice in the Description page of Project Settings.


#include "Carl.h"


// Sets default values
ACarl::ACarl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(RootComponent);

	
}

FString ACarl::OnInteract()
{
	FString InteractMessage;
	AIncompleteEvolutionCharacter* Player =Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!IsTurn)
	{
		if(FirstTouch == 0)
		{
			Player->InteractCharacterName = "Player";
			InteractMessage = "What is it?";
			FirstTouch +=1;
		}
		else if(FirstTouch == 1)
		{
			TurnOn();
			Player->InteractCharacterName = "? ? ?";
			InteractMessage = "Restarting";
			FirstTouch +=1;
		}
	}
	else
	{
		if(FirstTouch == 2)
		{
			InteractMessage = Introduce();
		}
		else if(FirstTouch>2)
		{
			InteractMessage = Talk();
		}
	}
	return InteractMessage;
}

void ACarl::TurnOn()
{
	IsTurn = true;
}

FString ACarl::Introduce()
{
	AIncompleteEvolutionCharacter* Player =Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FString InteractMessage;
	if(ConversationTime<IntroductionMessage.Num())
	{
		Player->InteractCharacterName = IntroductionCharacter[ConversationTime];
		InteractMessage = IntroductionMessage[ConversationTime];
		ConversationTime += 1;
		if(ConversationTime == IntroductionMessage.Num())
		{
			ConversationTime = 0;
			Player->InteractingEnd = true;
			Player->TargetUpdate = true;
			Player->TaskText = "3. Find the Key card";
			FirstTouch+=1;
		}
	}
	return InteractMessage;
}

FString ACarl::Talk()
{
	AIncompleteEvolutionCharacter* Player =Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FString InteractMessage;
	if(!Player->GetKey)
	{
		if(ConversationTime<ConversationMessage.Num())
		{
			Player->InteractCharacterName = ConversationCharacter[ConversationTime];
			InteractMessage = ConversationMessage[ConversationTime];
			ConversationTime += 1;
			if(ConversationTime == ConversationMessage.Num())
			{
				ConversationTime = 0;
				Player->InteractingEnd = true;
			}
		}
	}
	else
	{
		if(ConversationTime<ConversationMessage1.Num())
		{
			Player->InteractCharacterName = ConversationCharacter1[ConversationTime];
			InteractMessage = ConversationMessage1[ConversationTime];
			ConversationTime += 1;
			if(ConversationTime == ConversationMessage1.Num())
			{
				ConversationTime = 0;
				Player->InteractingEnd = true;
				Player->TargetUpdate=true;
				Player->TaskText = "Thanks! All is finished. Feel free to visit.";
			}
		}
	}
	return InteractMessage;
}

// Called when the game starts or when spawned
void ACarl::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACarl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


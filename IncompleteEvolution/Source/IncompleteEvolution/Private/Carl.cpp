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
		if(FirstTouch)
		{
			Player->InteractCharacterName = "Player";
			InteractMessage = "What is it?";
			FirstTouch = false;
		}
		else
		{
			TurnOn();
			Player->InteractCharacterName = "? ? ?";
			InteractMessage = "Starting up";
		}
	}
	else
	{
		InteractMessage = Talk();
		
	}
	return InteractMessage;
}

void ACarl::TurnOn()
{
	IsTurn = true;
}

FString ACarl::Talk()
{
	AIncompleteEvolutionCharacter* Player =Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FString InteractMessage;
	if(Time<ConversationMessage.Num())
	{
		Player->InteractCharacterName = ConversationCharacter[Time];
		InteractMessage = ConversationMessage[Time];
		Time += 1;
		if(Time == ConversationMessage.Num())
		{
			Time =0;
			Player->InteractingEnd = true;
			Player->TargetUpdate=true;
			Player->TaskText = "3. Find the Key card";
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


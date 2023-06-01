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
	FString InteractMessage = ReadMessage(IntroductionMessage,IntroductionCharacter,2);
	
	Player->TargetUpdate = true;
	
	return InteractMessage;
}

FString ACarl::Talk()
{
	FString InteractMessage;
	if(!Player->GetKey)
	{
		 InteractMessage = ReadMessage(ConversationMessage,ConversationCharacter,3);
	}
	else
	{
		InteractMessage = ReadMessage(ConversationMessage1,ConversationCharacter1,4);
		
	}
	return InteractMessage;
}

FString ACarl::ReadMessage(TArray<FString> Message, TArray<FString> Character,int Touch)
{
	FString InteractMessage;
	if(ConversationTime<Message.Num())
	{
		Player->InteractCharacterName = Character[ConversationTime];
		InteractMessage = Message[ConversationTime];
		ConversationTime += 1;
		if(ConversationTime == Message.Num())
		{
			ConversationTime = 0;
			Player->InteractingEnd = true;
			if(Touch==2)
			{
				Player->TaskText = "3. Find the Key card";
				FirstTouch+=1;
				SetActorLocation(FVector(-4419,1249,1114));
			}
			else if(Touch==4)
			{
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
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ACarl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/KeyCard.h"

#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"

// Sets default values
AKeyCard::AKeyCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
	MainBody->SetupAttachment(RootComponent);

}

FString AKeyCard::OnInteract()
{
	FString InteractMessage;
	InteractMessage = "Got it! It should be the key card! Now return to Carl!";
	AIncompleteEvolutionCharacter* Player =
		Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->InteractCharacterName = "Ethan";
	Player->InteractingEnd = true;
	Player->GetKey=true;
	
	this->Destroy();
	
	return InteractMessage;
}

// Called when the game starts or when spawned
void AKeyCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


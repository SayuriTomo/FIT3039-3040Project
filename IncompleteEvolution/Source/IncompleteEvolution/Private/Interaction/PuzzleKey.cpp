// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/PuzzleKey.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"

// Sets default values
APuzzleKey::APuzzleKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	RootComponent = MainBody;
	
}

FString APuzzleKey::OnInteract()
{
	FString InteractMessage;
	AIncompleteEvolutionCharacter* Player =
		Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(KeyTag)
	{
		Player->GetPuzzleKeyOne = true;
	}
	else
	{
		Player->GetPuzzleKeyTwo = true;
	}
	this->Destroy();
	Player->Interacting = false;
	return InteractMessage;
}

// Called when the game starts or when spawned
void APuzzleKey::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APuzzleKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


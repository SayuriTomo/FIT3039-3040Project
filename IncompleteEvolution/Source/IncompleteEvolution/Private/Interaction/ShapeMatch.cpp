// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/ShapeMatch.h"

#include "ActorGrab.h"

// Sets default values
AShapeMatch::AShapeMatch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(RootComponent);
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	CollisionBox->SetupAttachment(MainBody);

	KeyInsert = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Component"));
	KeyInsert->SetupAttachment(MainBody);
	
}

FString AShapeMatch::OnInteract()
{
	FString InteractMessage;
	if(!bHasPlaced&&!bFirstPlaced&&bIsNeedToInteract)
	{
		bool bIsKeyCorrect = false;
		if(bRequireOne&&Player->GetPuzzleKeyOne)
		{
			Player->GetPuzzleKeyOne = !Player->GetPuzzleKeyOne;
			bIsKeyCorrect = true;
		}
		else if(!bRequireOne&&Player->GetPuzzleKeyTwo)
		{
			Player->GetPuzzleKeyTwo = !Player->GetPuzzleKeyTwo;
			bIsKeyCorrect = true;
		}
		
		if(bIsKeyCorrect)
		{
			KeyInsert->SetVisibility(true);
			bFirstPlaced = true;
			bHasPlaced = true;
			bIsActive = false;
		}
		
	}

	Player->Interacting = false;
	Player->InteractingEnd = true;
	return InteractMessage;
}

// Called when the game starts or when spawned
void AShapeMatch::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!bIsNeedToInteract)
	{
		bIsActive = false;
	}
	KeyInsert->SetVisibility(false);
}



// Called every frame
void AShapeMatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TArray<AActor*> Actors;
	TSubclassOf<AActorGrab> ActorGrabs;
	GetOverlappingActors(Actors,ActorGrabs);
	if(Actors.IsEmpty())
	{
		bHasPlaced = false;
		bFirstPlaced = false;
	}
	for(AActor* Actor:Actors)
	{
		if(Cast<AActorGrab>(Actor)
			&&!Cast<AActorGrab>(Actor)->IsGrabbing
			&&!Cast<AActorGrab>(Actor)->IsFixing
			&&Cast<AActorGrab>(Actor)->ShapeSymbol == ShapeRequired
			&&Actor->GetActorScale3D().X<=CustomSize.X
			&&Actor->GetActorScale3D().Y<=CustomSize.Y
			&&Actor->GetActorScale3D().Z<=CustomSize.Z
			&&Actor->GetActorScale3D().X>=MinCustomSize.X
			&&Actor->GetActorScale3D().X>=MinCustomSize.Y
			&&Actor->GetActorScale3D().X>=MinCustomSize.Z
			&&!bHasPlaced)
		{
			if(!bFirstPlaced)
			{
				Actor->SetActorLocation(CollisionBox->GetComponentLocation());
				bFirstPlaced = true;
			}
			Actor->SetActorScale3D(CustomSize);
			Actor->SetActorRotation(CollisionBox->GetComponentRotation());
			bHasPlaced = true;
		}
	}
	
}



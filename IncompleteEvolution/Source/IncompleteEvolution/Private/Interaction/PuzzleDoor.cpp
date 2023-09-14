// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/PuzzleDoor.h"



// Sets default values
APuzzleDoor::APuzzleDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	KeyInsert = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Component"));
	PlayerCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Check Box Component"));
	
	PlayerCheckBox->SetupAttachment(RootComponent);
	KeyInsert -> SetupAttachment(DoorFrame);
	DoorFrame -> SetupAttachment(RootComponent);
	LeftDoor->SetupAttachment(RootComponent);
	RightDoor->SetupAttachment(RootComponent);

}

FString APuzzleDoor::OnInteract()
{
	FString InteractMessage;
	if(bIsPlayerRightSide)
	{
		if(bRequireOne)
		{
			if((Player->GetPuzzleKeyOne&&!bIsOpened)||(!Player->GetPuzzleKeyOne&&bIsOpened))
			{
				Operate();
				Player->GetPuzzleKeyOne = !Player->GetPuzzleKeyOne;
			}
			else
			{
				Player -> InteractCharacterName = "Player";
				InteractMessage = "I don't have this key";
			}
		}
		else if(!bRequireOne)
		{
			if((Player->GetPuzzleKeyTwo&&!bIsOpened)||(!Player->GetPuzzleKeyTwo&&bIsOpened))
			{
				Operate();
				Player->GetPuzzleKeyTwo = !Player->GetPuzzleKeyTwo;
			}
			else
			{
				Player -> InteractCharacterName = "Player";
				InteractMessage = "I don't have this key";
			}
		}
	}
	else
	{
		Player -> InteractCharacterName = "Player";
		InteractMessage = "I can't do this";
	}
	
	
	Player->InteractingEnd = true;
	return InteractMessage;
}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void APuzzleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	KeyInsert->SetVisibility(bIsOpened);
	
	bool bFoundPlayer = false;
	TArray<AActor*>Actors;
	TSubclassOf<AIncompleteEvolutionCharacter> PlayerClass;
	GetOverlappingActors(Actors,PlayerClass);
	for (AActor* Actor:Actors)
	{
		if(Cast<AIncompleteEvolutionCharacter>(Actor))
		{
			bFoundPlayer = true;
		}
	}
	bIsPlayerRightSide = bFoundPlayer;
	
	if(bIsOperating)
	{
		bIsActive = false;
		if(CurrentTime<TimeLimit)
		{
			if(!bIsOpened)
			{
				OpenDoor(DeltaTime);
			}
			else
			{
				CloseDoor(DeltaTime);
			}
			CurrentTime+=DeltaTime;
		}
		else
		{
			bIsActive = true;
			CurrentTime = 0;
			bIsOperating = false;
		}
	}
}

void APuzzleDoor::Operate()
{
	bIsOperating = true;
	Player->Interacting = false;
	bIsOpened = !bIsOpened;
	
}

void APuzzleDoor::OpenDoor(float DeltaTime)
{
	FVector LeftLocation = LeftDoor->GetComponentLocation();
	FVector RightLocation = RightDoor->GetComponentLocation();
	switch(OpenDirection)
	{
		case 0:
			{
				LeftDoor->SetWorldLocation(FVector(LeftLocation.X-MoveSpeed*DeltaTime,LeftLocation.Y,LeftLocation.Z));
				RightDoor->SetWorldLocation(FVector(RightLocation.X+MoveSpeed*DeltaTime,RightLocation.Y,RightLocation.Z));
				break;
			}
		case 1:
			{
				LeftDoor->SetWorldLocation(FVector(LeftLocation.X+MoveSpeed*DeltaTime,LeftLocation.Y,LeftLocation.Z));
				RightDoor->SetWorldLocation(FVector(RightLocation.X-MoveSpeed*DeltaTime,RightLocation.Y,RightLocation.Z));
				break;
			}
		case 2:
			{
				LeftDoor->SetWorldLocation(FVector(LeftLocation.X,LeftLocation.Y-25*DeltaTime,LeftLocation.Z));
				RightDoor->SetWorldLocation(FVector(RightLocation.X,RightLocation.Y+25*DeltaTime,RightLocation.Z));
				break;
			}
		case 3:
			{
				LeftDoor->SetWorldLocation(FVector(LeftLocation.X,LeftLocation.Y+25*DeltaTime,LeftLocation.Z));
				RightDoor->SetWorldLocation(FVector(RightLocation.X,RightLocation.Y-25*DeltaTime,RightLocation.Z));
				break;
			}
		default:{}
	}
	
	
}

void APuzzleDoor::CloseDoor(float DeltaTime)
{
	FVector LeftLocation = LeftDoor->GetComponentLocation();
	FVector RightLocation = RightDoor->GetComponentLocation();
	switch(OpenDirection)
	{
	case 0:
		{
			LeftDoor->SetWorldLocation(FVector(LeftLocation.X+MoveSpeed*DeltaTime,LeftLocation.Y,LeftLocation.Z));
			RightDoor->SetWorldLocation(FVector(RightLocation.X-MoveSpeed*DeltaTime,RightLocation.Y,RightLocation.Z));
			break;
		}
	case 1:
		{
			LeftDoor->SetWorldLocation(FVector(LeftLocation.X-MoveSpeed*DeltaTime,LeftLocation.Y,LeftLocation.Z));
			RightDoor->SetWorldLocation(FVector(RightLocation.X+MoveSpeed*DeltaTime,RightLocation.Y,RightLocation.Z));
			break;
		}
	case 2:
		{
			LeftDoor->SetWorldLocation(FVector(LeftLocation.X,LeftLocation.Y+25*DeltaTime,LeftLocation.Z));
			RightDoor->SetWorldLocation(FVector(RightLocation.X,RightLocation.Y-25*DeltaTime,RightLocation.Z));
			break;
		}
	case 3:
		{
			LeftDoor->SetWorldLocation(FVector(LeftLocation.X,LeftLocation.Y-25*DeltaTime,LeftLocation.Z));
			RightDoor->SetWorldLocation(FVector(RightLocation.X,RightLocation.Y+25*DeltaTime,RightLocation.Z));
			break;
		}
	default:{}
	}
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "LabDoor.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALabDoor::ALabDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	LeftDoor->SetupAttachment(RootComponent);
	RightDoor->SetupAttachment(RootComponent);
}

FString ALabDoor::OnInteract()
{
	FString InteractMessage;
	AIncompleteEvolutionCharacter* Player =
		Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if(IsLocked&&!Player->GetKey)
	{
		Player -> InteractCharacterName = "Player";
		InteractMessage = "It seems to be locked";
		Player->InteractingEnd = true;
		return InteractMessage;
	}
	else
	{
		if(KeyOpen)
		{
			OpenDoor();
			Player->Interacting = false;
		}
		else
		{
			Player -> InteractCharacterName = "Player";
			InteractMessage = "It seems to be locked";
			Player->InteractingEnd = true;
			return InteractMessage;
		}
		return InteractMessage;
	}
}

void ALabDoor::OpenDoor()
{
	bIsOpening = true;
	bIsActive = false;
	UGameplayStatics::PlaySoundAtLocation(this, Voice_DoorOpen, GetActorLocation());
}

// Called when the game starts or when spawned
void ALabDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALabDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsOpening)
	{
		if(CurrentTime<TimeLimit)
		{
			
			FVector LeftLocation = LeftDoor->GetComponentLocation();
			FVector RightLocation = RightDoor->GetComponentLocation();
			if(OpenDirection)
			{
				LeftDoor->SetWorldLocation(FVector(LeftLocation.X-75*DeltaTime,LeftLocation.Y,LeftLocation.Z));
				RightDoor->SetWorldLocation(FVector(RightLocation.X+75*DeltaTime,RightLocation.Y,RightLocation.Z));
			}
			else
			{
				LeftDoor->SetWorldLocation(FVector(LeftLocation.X,LeftLocation.Y-75*DeltaTime,LeftLocation.Z));
				RightDoor->SetWorldLocation(FVector(RightLocation.X,RightLocation.Y+75*DeltaTime,RightLocation.Z));
			}
			CurrentTime+=DeltaTime;
		}
		else
		{
			bIsOpening=false;
			this->Destroy();
		}
	}

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "LabDoor.h"

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
	if(IsLocked)
	{
		InteractMessage = "It seems to be locked";
		return InteractMessage;
	}
	else
	{
		OpenDoor();
		return InteractMessage;
	}
}

void ALabDoor::OpenDoor()
{
	Opening = true;
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
	if(Opening)
	{
		if(CurrentTime<TimeLimit)
		{
			FVector LeftLocation = LeftDoor->GetComponentLocation();
			FVector RightLocation = RightDoor->GetComponentLocation();\
			LeftDoor->SetWorldLocation(FVector(LeftLocation.X-25*DeltaTime,LeftLocation.Y,LeftLocation.Z));
			RightDoor->SetWorldLocation(FVector(RightLocation.X+25*DeltaTime,RightLocation.Y,RightLocation.Z));
			CurrentTime+=DeltaTime;
		}
		else
		{
			Opening=false;
			this->Destroy();
		}
	}

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	UpGate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up Gate"));
	DownGate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down Gate"));
	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light Component"));
	
	UpGate->SetupAttachment(RootComponent);
	DownGate->SetupAttachment(RootComponent);
	SpotLightComp -> SetupAttachment(RootComponent);

}

FString AGate::OnInteract()
{
	FString InteractMessage;
	AIncompleteEvolutionCharacter* Player =
		Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	OpenDoor();
	Player->Interacting = false;
	return InteractMessage;
}

void AGate::OpenDoor()
{
	bIsOpening = true;
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
	SpotLightComp -> SetVisibility(false);
}

// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsOpening)
	{
		if(CurrentTime<TimeLimit)
		{
			
			FVector UpLocation = UpGate->GetComponentLocation();
			FVector DownLocation = DownGate->GetComponentLocation();
			
			UpGate->SetWorldLocation(FVector(UpLocation.X,UpLocation.Y,UpLocation.Z+75*DeltaTime));
			DownGate->SetWorldLocation(FVector(DownLocation.X,DownLocation.Y,DownLocation.Z-75*DeltaTime));
			CurrentTime+=DeltaTime;
		}
		else
		{
			bIsOpening=false;
			SpotLightComp -> SetVisibility(true);
			UpGate->SetVisibility(false);
			DownGate->SetVisibility(false);
		}
	}
}




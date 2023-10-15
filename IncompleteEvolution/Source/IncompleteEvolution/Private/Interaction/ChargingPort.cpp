// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/ChargingPort.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChargingPort::AChargingPort()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lower Mesh"));
	LowerMesh->SetupAttachment(RootComponent);
	
	UpperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Upper Mesh"));
	UpperMesh->SetupAttachment(LowerMesh);
	
	CarlMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Carl Mesh1"));
	CarlMesh1->SetupAttachment(LowerMesh);

	CarlMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Carl Mesh2"));
	CarlMesh2->SetupAttachment(LowerMesh);
	
}

FString AChargingPort::OnInteract()
{
	FString InteractMessage;
	if(!SecondChargingPort)
	{
		return FirstInteract();
	}
	else
	{
		return SecondInteract();
	}
	return InteractMessage;
}

FString AChargingPort::SecondInteract()
{
	if(bIsActive)
	{
		CarlMesh1->SetVisibility(true);
		CarlMesh2->SetVisibility(true);
		bIsActive = false;
	}
	Time += 1;
		
	if(Time == 10)
	{
		if(GateControlled)
		{
			GateControlled -> OpenDoor();
		}
		if(!CanActivateFlash)
		{
			AIncompleteEvolutionCharacter* Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			Player->bIsScanAvailable = true;
			Player->TargetUpdate = true;
			Player->TaskText = nullptr;
		}
	}
	return CarlActor->ChargingTwo();
}

FString AChargingPort::FirstInteract()
{
	if(bIsActive)
	{
		CarlMesh1->SetVisibility(true);
		CarlMesh2->SetVisibility(true);
		bIsActive = false;
	}
	Time += 1;
		
	if(Time == 7)
	{
		if(GateControlled)
		{
			GateControlled -> OpenDoor();
		}
		if(CanActivateFlash)
		{
			AIncompleteEvolutionCharacter* Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			Player->bIsFlashLightAvailable = true;
			Player->TargetUpdate = true;
			Player->TaskText = "Move to the next room";
			Time = 0;
		}
	}
	return CarlActor->Charging();
}


// Called when the game starts or when spawned
void AChargingPort::BeginPlay()
{
	Super::BeginPlay();
	CarlMesh1->SetVisibility(false);
	CarlMesh2->SetVisibility(false);
	
	TArray<AActor*> ActorsToFind;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AActor::StaticClass(),ActorsToFind);
	for (AActor* Actor: ActorsToFind)
	{
		if(Cast<ACarl>(Actor))
		{
			CarlActor =  Cast<ACarl>(Actor);
		}
	}

	if(SecondChargingPort)
	{
		UpperMesh->SetMaterial(1,RedMaterial);
		UpperMesh->SetMaterial(2,RedMaterial);
		bIsActive = false;
	}
	
}

// Called every frame
void AChargingPort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SecondPortTick();
	
}

void AChargingPort::SecondPortTick()
{
	if(SecondChargingPort)
	{
		bool bIsRotationCompleted = false;
		if(RotationDevice)
		{
			if(RotationDevice->IsComplete)
			{
				UpperMesh->SetMaterial(1,GreenMaterial);
				bIsRotationCompleted = true;
			}
		}

		bool bIsAllShapeMatchComplete = false;
		for(AShapeMatch* EachMatch:ShapeMatches)
		{
			if(EachMatch->bHasPlaced)
			{
				bIsAllShapeMatchComplete = true;
			}
			else
			{
				bIsAllShapeMatchComplete = false;
				break;
			}
		}
		if(bIsAllShapeMatchComplete)
		{
			UpperMesh->SetMaterial(2,GreenMaterial);
		}
		if(bIsRotationCompleted&&bIsAllShapeMatchComplete)
		{
			bIsActive = true;
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingPort.h"
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
	if(!IsActive)
	{
		CarlMesh1->SetVisibility(true);
		CarlMesh2->SetVisibility(true);
		IsActive = true;
	}
	Time += 1;
	if(Time == 9)
	{
		CarlActor->MovePPVolume();
	}
	if(Time == 14)
	{
		CarlActor->Player->IsEnd = true;
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
}

// Called every frame
void AChargingPort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


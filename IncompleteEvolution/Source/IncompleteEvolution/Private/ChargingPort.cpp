// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingPort.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChargingPort::AChargingPort()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(RootComponent);
}

FString AChargingPort::OnInteract()
{
	FString InteractMessage;
	return InteractMessage;
}


// Called when the game starts or when spawned
void AChargingPort::BeginPlay()
{
	Super::BeginPlay();
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


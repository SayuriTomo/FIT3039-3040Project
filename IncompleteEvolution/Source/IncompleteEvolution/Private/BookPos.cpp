// Fill out your copyright notice in the Description page of Project Settings.


#include "BookPos.h"

// Sets default values
ABookPos::ABookPos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Position = CreateDefaultSubobject<UBoxComponent>(TEXT("Pos Component"));
	SetRootComponent(Position);

}

// Called when the game starts or when spawned
void ABookPos::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABookPos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> Actors;
	TSubclassOf<ABook> BooksClass;
	GetOverlappingActors(Actors,BooksClass);

	if(Actors.IsEmpty())
	{
		bHasPlaced = false;
		bFirstPlaced = false;
	}
	
	for(AActor* Actor:Actors)
	{
		if(Cast<ABook>(Actor))
		{
			if(BookRequired == Cast<ABook>(Actor)->BookNum&&!bHasPlaced)
			{
				if(!bFirstPlaced)
				{
					Actor->SetActorLocation(FVector(Position->GetComponentLocation().X+20,Position->GetComponentLocation().Y,Position->GetComponentLocation().Z));
					Actor->SetActorScale3D(FVector(0.9,0.9,0.9));
					Actor->SetActorRotation(Position->GetComponentRotation());
					bFirstPlaced = true;
					bHasPlaced = true;
				}
			}
		}
	}

}


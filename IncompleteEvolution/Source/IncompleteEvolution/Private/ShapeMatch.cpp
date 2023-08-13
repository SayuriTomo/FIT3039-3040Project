// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeMatch.h"

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
	
	
}

// Called when the game starts or when spawned
void AShapeMatch::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AShapeMatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		TArray<AActor*> Actors;
		TSubclassOf<AActorGrab> ActorGrabs;
		GetOverlappingActors(Actors,ActorGrabs);
		for(AActor* Actor:Actors)
		{
			if(Cast<AActorGrab>(Actor)
				&&!Cast<AActorGrab>(Actor)->IsGrabbing
				&&!Cast<AActorGrab>(Actor)->IsFixing
				&&Cast<AActorGrab>(Actor)->ShapeSymbol == ShapeRequired
				&&Actor->GetActorScale3D().X<=CollisionBox->GetRelativeScale3D().X
				&&Actor->GetActorScale3D().Y<=CollisionBox->GetRelativeScale3D().Y
				&&Actor->GetActorScale3D().Z<=CollisionBox->GetRelativeScale3D().Z
				&&bHasPlaced)
			{
				Actor->SetActorLocation(CollisionBox->GetComponentLocation());
				Actor->SetActorScale3D(CollisionBox->GetRelativeScale3D());
				Actor->SetActorRotation(CollisionBox->GetComponentRotation());
				bHasPlaced = false;
			}
			else
			{
				bHasPlaced = true;
			}
		}
}



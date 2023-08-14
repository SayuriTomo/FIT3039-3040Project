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

	CollisionBoxUp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component UP"));
	CollisionBoxDown = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component Down"));
	CollisionBoxUp->SetupAttachment(MainBody);
	CollisionBoxDown->SetupAttachment(MainBody);
	
	
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
	if(Actors.IsEmpty())
	{
		bHasPlaced=false;
	}
	for(AActor* Actor:Actors)
	{
		if(Cast<AActorGrab>(Actor)
			&&!Cast<AActorGrab>(Actor)->IsGrabbing
			&&!Cast<AActorGrab>(Actor)->IsFixing
			&&Cast<AActorGrab>(Actor)->ShapeSymbol == ShapeRequired
			&&Actor->GetActorScale3D().X<=CollisionBoxUp->GetRelativeScale3D().X
			&&Actor->GetActorScale3D().Y<=CollisionBoxUp->GetRelativeScale3D().Y
			&&Actor->GetActorScale3D().Z<=CollisionBoxUp->GetRelativeScale3D().Z
			&&!bHasPlaced)
		{
			Actor->SetActorLocation(CollisionBoxUp->GetComponentLocation());
			Actor->SetActorScale3D(FVector(0.5,0.5,0.5));
			Actor->SetActorRotation(CollisionBoxUp->GetComponentRotation());
			bHasPlaced = true;
		}
	}
	
}



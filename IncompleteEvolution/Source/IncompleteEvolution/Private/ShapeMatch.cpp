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
	if(Actors.IsEmpty())
	{
		bHasPlaced = false;
		bFirstPlaced = false;
	}
	for(AActor* Actor:Actors)
	{
		if(Cast<AActorGrab>(Actor)
			&&!Cast<AActorGrab>(Actor)->IsGrabbing
			&&!Cast<AActorGrab>(Actor)->IsFixing
			&&Cast<AActorGrab>(Actor)->ShapeSymbol == ShapeRequired
			&&Actor->GetActorScale3D().X<=CustomSize.X
			&&Actor->GetActorScale3D().Y<=CustomSize.Y
			&&Actor->GetActorScale3D().Z<=CustomSize.Z
			&&Actor->GetActorScale3D().X>=MinCustomSize.X
			&&Actor->GetActorScale3D().X>=MinCustomSize.Y
			&&Actor->GetActorScale3D().X>=MinCustomSize.Z
			&&!bHasPlaced)
		{
			if(!bFirstPlaced)
			{
				Actor->SetActorLocation(CollisionBox->GetComponentLocation());
				bFirstPlaced = true;
			}
			Actor->SetActorScale3D(CustomSize);
			Actor->SetActorRotation(CollisionBox->GetComponentRotation());
			bHasPlaced = true;
		}
	}
	
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorGrab.h"

// Sets default values
AActorGrab::AActorGrab()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetupAttachment(RootComponent);
	ActorMesh->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AActorGrab::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorGrab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsGrabbing)
	{
		ActorMesh->SetCastShadow(false);
	}
	else
	{
		ActorMesh->SetCastShadow(true);
		if(IsFixing)
		{
			ActorMesh->SetSimulatePhysics(false);
		}
		else
		{
			ActorMesh->SetSimulatePhysics(true);
		}
	}

	


}


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
	FBodyInstance* BodyInst = ActorMesh->GetBodyInstance();
	if(BodyInst)
	{
		BodyInst->MassScale = 10;  
		BodyInst->UpdateMassProperties();
	}
}

// Called every frame
void AActorGrab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsGrabbing)
	{
		ActorMesh->SetCastShadow(false);
		ActorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	}
	else
	{
		ActorMesh->SetCastShadow(true);
		ActorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Block);
		if(IsFixing)
		{
			ActorMesh->SetSimulatePhysics(false);
			ActorMesh->SetMaterial(0,FixMaterial);
		}
		else
		{
			ActorMesh->SetSimulatePhysics(true);
			ActorMesh->SetMaterial(0,OriginalMaterial);
		}
	}
}


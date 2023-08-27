// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/XylophoneMain.h"

// Sets default values
AXylophoneMain::AXylophoneMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AXylophoneMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXylophoneMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bIsAnyCompPlaying = false;
	for(AXylophoneComponent* ChildActor:ChildrenActors)
	{
		if(ChildActor->bIsPlaying)
		{
			bIsAnyCompPlaying = true;
		}
	}

	if(bIsAnyCompPlaying)
	{
		if(Time>0)
		{
			for(AXylophoneComponent* ChildActor:ChildrenActors)
			{
				ChildActor->bCanBePlayed = false;
			}
		}
		else
		{
			for(AXylophoneComponent* ChildActor:ChildrenActors)
			{
				ChildActor->bCanBePlayed = true;
				bIsAnyCompPlaying = false;
				Time = 0.5f;
			}
		}
		Time-= DeltaTime;
		
	}

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/XylophoneMain.h"

#include "Kismet/GameplayStatics.h"

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
	
	if(CurrentKeyPressed == KeyOrderRequired && !bIsAchieved)
	{
		bIsAchieved = true;
		bPreparePlaySuccess = true;
	}

	if(bPreparePlaySuccess)
	{
		PrepareTime -= DeltaTime;
		if(PrepareTime<=0)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SuccessVoice, GetActorLocation());
			bPreparePlaySuccess = false;
		}
	}
	
	for(AXylophoneComponent* ChildActor:ChildrenActors)
	{
		if(ChildActor->bIsPlaying)
		{
			CurrentKeyPressed.Add(ChildActor->KeyTag);
			if(CurrentKeyPressed.Num()>KeyOrderRequired.Num())
			{
				CurrentKeyPressed.RemoveAt(0);
			}
			ChildActor->bIsPlaying = false;
		}
	}
}


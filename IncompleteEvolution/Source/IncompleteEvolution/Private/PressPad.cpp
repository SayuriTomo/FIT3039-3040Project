// Fill out your copyright notice in the Description page of Project Settings.


#include "PressPad.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APressPad::APressPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	CollisionBox->SetupAttachment(MainBody);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APressPad::BoxOverlapBegin);
	
}

// Called when the game starts or when spawned
void APressPad::BeginPlay()
{
	Super::BeginPlay();
}

void APressPad::BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		if(DoorActor)
		{
			DoorActor->OpenDoor();
		}
	}
}

// Called every frame
void APressPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


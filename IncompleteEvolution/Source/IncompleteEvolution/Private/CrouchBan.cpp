// Fill out your copyright notice in the Description page of Project Settings.


#include "CrouchBan.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"

// Sets default values
ACrouchBan::ACrouchBan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BanBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Ban Box Component"));
	BanBox->SetupAttachment(RootComponent);

	BanBox->OnComponentBeginOverlap.AddDynamic(this, &ACrouchBan::BoxOverlapBegin);
	BanBox->OnComponentEndOverlap.AddDynamic(this, &ACrouchBan::BoxOverlapEnd);
}

// Called when the game starts or when spawned
void ACrouchBan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrouchBan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrouchBan::BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this && Cast<AIncompleteEvolutionCharacter>(OtherActor))
	{
		Cast<AIncompleteEvolutionCharacter>(OtherActor)->AllowStand=false;
		if(!Cast<AIncompleteEvolutionCharacter>(OtherActor)->WhetherCrouch)
		{
			Cast<AIncompleteEvolutionCharacter>(OtherActor)->WhetherCrouch = true;
		}
	}
}

void ACrouchBan::BoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if(OtherActor && OtherActor != this && Cast<AIncompleteEvolutionCharacter>(OtherActor))
	{
		Cast<AIncompleteEvolutionCharacter>(OtherActor)->AllowStand=true;
		if(Cast<AIncompleteEvolutionCharacter>(OtherActor)->WhetherCrouch)
		{
			Cast<AIncompleteEvolutionCharacter>(OtherActor)->WhetherCrouch = false;
		}
	}
}


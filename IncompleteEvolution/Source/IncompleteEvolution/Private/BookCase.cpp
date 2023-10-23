// Fill out your copyright notice in the Description page of Project Settings.


#include "BookCase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABookCase::ABookCase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CaseLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Case"));
	CaseMid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mid Case"));
	CaseRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Case"));
	
	CaseLeft->SetupAttachment(RootComponent);
	CaseMid->SetupAttachment(CaseLeft);
	CaseRight->SetupAttachment(CaseLeft);
}

// Called when the game starts or when spawned
void ABookCase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABookCase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsOperating)
	{
		if(CurrentTime<TimeLimit)
		{
			
			FVector MidLocation = CaseMid->GetComponentLocation();
			CaseMid->SetWorldLocation(FVector(MidLocation.X,MidLocation.Y-50*DeltaTime,MidLocation.Z));
			CurrentTime+=DeltaTime;
		}
		else
		{
			bIsOperating=false;
		}
	}
	
	bool bAllPosPlaced = true;
	for(ABookPos* EachPos:BooksPos)
	{
		if(!EachPos->bHasPlaced)
		{
			bAllPosPlaced = false;
			break;
		}
	}
	
	if(bAllPosPlaced&&!bIsCompleted)
	{
		bIsCompleted = true;
		bIsOperating = true;
		UGameplayStatics::PlaySoundAtLocation(this, Voice_DoorOpen, GetActorLocation());
	}

}


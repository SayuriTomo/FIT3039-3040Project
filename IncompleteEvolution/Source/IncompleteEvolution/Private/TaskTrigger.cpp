// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskTrigger.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATaskTrigger::ATaskTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box Component"));
	SetRootComponent(TriggerBox);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATaskTrigger::TriggerOverlap);
}

// Called when the game starts or when spawned
void ATaskTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaskTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaskTrigger::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!TimeLimit)
	{
		if(OtherActor && OtherActor != this && Cast<AIncompleteEvolutionCharacter>(OtherActor))
		{
			if(Voice_Achieve)
			{
				UGameplayStatics::PlaySoundAtLocation(this, Voice_Achieve, GetActorLocation());
			}
			AIncompleteEvolutionCharacter* Player = Cast<AIncompleteEvolutionCharacter>(OtherActor);
			Player->Interacting =true;
			if(!TaskMessage.IsEmpty())
			{
				Player->TargetUpdate=true;
				Player->TaskText = TaskMessage;
			}
			
			Player->InteractCharacterName = CharacterName;
			Player->InteractText = InteractMessage;
			Player->InteractingEnd = true;
			TimeLimit = true;
		}
	}
}



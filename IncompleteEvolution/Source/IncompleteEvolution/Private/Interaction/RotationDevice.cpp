// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/RotationDevice.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARotationDevice::ARotationDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
	MainBody->SetupAttachment(RootComponent);
}

FString ARotationDevice::OnInteract()
{
	IsRotating = true;
	Player->Interacting=false;
	return "";
}

// Called when the game starts or when spawned
void ARotationDevice::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Called every frame
void ARotationDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsActive)
	{
		if(IsRotating)
		{
			FRotator CurrentRotation = this->GetActorRotation();
			FRotator NextRotation = FRotator(CurrentRotation.Pitch,CurrentRotation.Yaw+1,CurrentRotation.Roll);
			RotationDegree += 1;
			SetActorRotation(NextRotation);
			if(RotationDegree % 90 ==0)
			{
				IsRotating = false;
				if(RotationDegree >= 360)
				{
					RotationDegree = 0;
				}
			}
		}
		
		if(IsParent)
		{
			if(this->RotationDegree == TargetDegree)
			{
				for(ARotationDevice* ChildActor:ChildrenActor)
				{
					if(ChildActor->RotationDegree == ChildActor->TargetDegree)
					{
						IsComplete = true;
					}
					else
					{
						IsComplete = false;
						break;
					}
				}
			}

			if(IsComplete)
			{
				UGameplayStatics::PlaySoundAtLocation(this, Voice_Complete, GetActorLocation());
				IsActive =false;
				for(ARotationDevice* ChildActor:ChildrenActor)
				{
					ChildActor->IsActive=false;
				}
			}
		}
	}
}


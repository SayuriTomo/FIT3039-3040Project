// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/XylophoneComponent.h"

#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AXylophoneComponent::AXylophoneComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Component"));
	Component->SetupAttachment(RootComponent);
}

FString AXylophoneComponent::OnInteract()
{
	if(bCanBePlayed)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Voice, GetActorLocation());
	}
	AIncompleteEvolutionCharacter* Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->Interacting=false;
	return "";
}

// Called when the game starts or when spawned
void AXylophoneComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXylophoneComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


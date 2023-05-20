// Fill out your copyright notice in the Description page of Project Settings.


#include "Carl.h"

// Sets default values
ACarl::ACarl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FString ACarl::OnInteract()
{
	TurnOn();
	return ConversationMessage1[1];
}

void ACarl::TurnOn()
{
	IsTurn = true;
}

void ACarl::Talk()
{
}

// Called when the game starts or when spawned
void ACarl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


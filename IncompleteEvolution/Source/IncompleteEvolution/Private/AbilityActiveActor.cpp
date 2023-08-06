// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityActiveActor.h"

// Sets default values
AAbilityActiveActor::AAbilityActiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
	MainBody->SetupAttachment(RootComponent);


}

FString AAbilityActiveActor::OnInteract()
{
	return ReadMessage(M_AbilityLearn,C_AbilityLearn);
}

FString AAbilityActiveActor::ReadMessage(TArray<FString> Message, TArray<FString> Character)
{
	FString InteractMessage;
	if(Index<Message.Num())
	{
		Player->InteractCharacterName = Character[Index];
		InteractMessage =Message[Index];
		Index += 1;
		if(Index == Message.Num())
		{
			Player->InteractingEnd = true;
			Player->bIsGrabActive = true;
		}
	}
	return InteractMessage;
}

// Called when the game starts or when spawned
void AAbilityActiveActor::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

// Called every frame
void AAbilityActiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


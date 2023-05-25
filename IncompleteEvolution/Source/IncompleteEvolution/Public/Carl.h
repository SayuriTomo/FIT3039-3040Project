// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "Carl.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ACarl : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarl();

	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;
	
	void TurnOn();
	FString Introduce();
	FString Talk();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float FirstTouch = 0;
	bool IsTurn = false;
	bool IsTalk = false;
	
	int ConversationTime;

	UPROPERTY(EditAnywhere)
	TArray<FString> IntroductionMessage={"Hi,Ethan","Who are you","That's weird, but I amd Carl",
		"I am sure that we know each other", "...","So my name is Ethan","Sure",
		"Sorry, I don't remember anything","Oh, it must be the side effect","Side effect? What happened on me?",
		"Access restriction!","It seems I don't have permission to access this","Could you find a key card for me?","It may help me access to this level",
		"The card should be in Room 1"};

	UPROPERTY(EditAnywhere)
	TArray<FString> IntroductionCharacter = {"? ? ?","Player","? ? ?",
		"Carl","Player","Ethan","Carl",
		"Ethan","Carl","Ethan",
		"Carl","Carl","Carl","Carl",
		"Carl"};

	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationMessage = {"It seems you don't get the key card","It should be in Room 1"};
	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationCharacter ={"Carl", "Carl"};

	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationMessage1 = {"You got it!"};
	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationCharacter1 ={"Carl"};
};

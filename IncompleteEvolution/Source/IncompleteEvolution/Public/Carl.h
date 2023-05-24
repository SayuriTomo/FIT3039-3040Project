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
	FString Talk();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool FirstTouch = true;
	bool IsTurn = false;
	bool IsTalk = false;
	
	int Time;
	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationMessage={"Hi,Ethan","Who is Ethan","I'm fine thank you and you"};

	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationCharacter = {"? ? ?","? ? ?","? ? ?"};
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "AbilityActiveActor.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AAbilityActiveActor : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityActiveActor();

	UFUNCTION()
	virtual FString OnInteract();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	AIncompleteEvolutionCharacter* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString ReadMessage(TArray<FString> Message,
		TArray<FString> Character);

	TArray<FString> M_AbilityLearn = {"Code 3040",
		"Heart rate is 101",
		"Sign stability",
		"Implant ability is",
		"Resize",
		"Ability use method prediction is",
		"Use the left mouse button to click the specific object",
		"and drag the field of view",
		"Resize?",
		"What does it mean?"};
	UPROPERTY(EditAnywhere)
	TArray<FString> C_AbilityLearn ={
		"Report","Report","Report","Report","Report","Report","Report","Report",
		"Player","Player"};

	int Index = 0;
};

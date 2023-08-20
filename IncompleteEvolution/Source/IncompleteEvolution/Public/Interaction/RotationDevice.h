// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "RotationDevice.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ARotationDevice : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotationDevice();

	UFUNCTION()
	virtual FString OnInteract();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;

	int RotationDegree = 0;
	UPROPERTY(EditAnywhere) float TargetDegree;
	bool IsComplete = false;
	UPROPERTY(EditAnywhere)bool IsActive = true;
	
	UPROPERTY(EditAnywhere)bool IsParent;
	UPROPERTY(EditAnywhere)TArray<ARotationDevice*> ChildrenActor;
	
	AIncompleteEvolutionCharacter* Player;

	UPROPERTY(EditAnywhere)
	USoundBase* Voice_Complete;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsRotating = false;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/BoxComponent.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "PuzzleDoor.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API APuzzleDoor : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleDoor();

	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftDoor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* PlayerCheckBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* KeyInsert;

	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	int OpenDirection = 0;

	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	bool bIsOpened = false;

	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	bool bRequireOne = false;

	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	bool bIsOperating = false;

	float CurrentTime;
	
	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	float TimeLimit;

	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	float MoveSpeed;

	void OpenDoor(float DeltaTime);

	void CloseDoor(float DeltaTime);

	void Operate();
	
	AIncompleteEvolutionCharacter* Player;

	FVector LeftInitialLocation;
	FVector RightInitialLocation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};



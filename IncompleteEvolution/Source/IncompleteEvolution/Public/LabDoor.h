// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "LabDoor.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ALabDoor : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabDoor();

	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeftDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RightDoor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Opening = false;
	float CurrentTime;
	const float TimeLimit = 5;
	
	UPROPERTY(EditAnywhere)
	bool IsLocked;
	
	UFUNCTION()
	void OpenDoor();

};

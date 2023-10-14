// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carl.h"
#include "Gate.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "ChargingPort.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AChargingPort : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChargingPort();
	
	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* UpperMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CarlMesh1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* CarlMesh2;

	ACarl* CarlActor;

	float Time = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)AGate* GateControlled;

	UPROPERTY(EditAnywhere)bool CanActivateFlash;

};

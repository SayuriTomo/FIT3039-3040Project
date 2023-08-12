// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Components/SpotLightComponent.h"
#include "Gate.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AGate : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGate();
	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* UpGate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DownGate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpotLightComponent* SpotLightComp;

	bool bIsOpening = false;
	float CurrentTime;
	const float TimeLimit = 4;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OpenDoor();
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "XylophoneComponent.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AXylophoneComponent : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXylophoneComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Component;

	virtual FString OnInteract() override;
	
	bool bCanBePlayed = true;
	bool bIsPlaying = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USoundBase* Voice;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

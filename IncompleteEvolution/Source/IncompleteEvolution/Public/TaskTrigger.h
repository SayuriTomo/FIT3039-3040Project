// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TaskTrigger.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ATaskTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskTrigger();
	UPROPERTY(EditAnywhere)UBoxComponent* TriggerBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	FString TaskMessage;

	UPROPERTY(EditAnywhere)
	FString InteractMessage;
	
	UPROPERTY(EditAnywhere)
	FString CharacterName;

	bool TimeLimit=false;

	UPROPERTY(EditAnywhere)
	USoundBase* Voice_Trigger;

	UPROPERTY(EditAnywhere)
	USoundBase* Voice_Achieve;
};


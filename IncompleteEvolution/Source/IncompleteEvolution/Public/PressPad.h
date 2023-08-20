// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/LabDoor.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PressPad.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API APressPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressPad();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UStaticMeshComponent* MainBody;
	UPROPERTY(EditAnywhere)UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	ALabDoor* DoorActor;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorGrab.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AActorGrab : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)UStaticMeshComponent* ActorMesh;
	
public:	
	// Sets default values for this actor's properties
	AActorGrab();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* OriginalMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* FixMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsGrabbing = false;

	bool IsFixing=false;

	UPROPERTY(EditAnywhere)
	bool CanBeSingleGrab = true;

};

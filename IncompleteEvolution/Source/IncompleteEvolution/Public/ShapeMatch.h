// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ShapeMatch.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AShapeMatch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShapeMatch();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UStaticMeshComponent* MainBody;
	UPROPERTY(EditAnywhere)UBoxComponent* CollisionBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bHasPlaced;

	UPROPERTY(EditAnywhere)
	int ShapeRequired;

};

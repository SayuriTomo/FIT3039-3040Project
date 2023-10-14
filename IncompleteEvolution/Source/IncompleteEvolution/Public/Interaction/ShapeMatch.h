// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InteractInterface.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "ShapeMatch.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AShapeMatch : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShapeMatch();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UStaticMeshComponent* MainBody;
	UPROPERTY(EditAnywhere)UBoxComponent* CollisionBox;
	
	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AIncompleteEvolutionCharacter* Player;

	bool bHasPlaced;
	bool bFirstPlaced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* KeyInsert;

	UPROPERTY(EditAnywhere)
	int ShapeRequired;

	UPROPERTY(EditAnywhere)
	FVector CustomSize;

	UPROPERTY(EditAnywhere)
	FVector MinCustomSize;

	UPROPERTY(EditAnywhere)
	bool bIsNeedToInteract;

	UPROPERTY(EditAnywhere)
	bool bRequireOne = false;

};

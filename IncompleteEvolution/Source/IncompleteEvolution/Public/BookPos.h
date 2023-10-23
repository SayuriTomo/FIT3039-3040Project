// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Book.h"
#include "BookPos.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ABookPos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABookPos();
	
	UPROPERTY(EditAnywhere)UBoxComponent* Position;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bHasPlaced = false;
	bool bFirstPlaced = false;
	UPROPERTY(EditAnywhere)int BookRequired;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "PuzzleKey.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API APuzzleKey : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleKey();

	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;

	UPROPERTY(EditAnywhere)
	bool KeyTag = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

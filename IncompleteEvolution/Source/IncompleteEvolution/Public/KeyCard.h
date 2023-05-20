// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "KeyCard.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AKeyCard : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyCard();
	
	UFUNCTION()
	virtual FString OnInteract() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

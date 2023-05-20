// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Carl.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ACarl : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarl();

	UFUNCTION()
	virtual FString OnInteract()override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;

	void TurnOn();
	void Talk();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsTurn = false;
	bool IsTalk = false;
	
	int Time;
	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationMessage1;

	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationMessage2;

	UPROPERTY(EditAnywhere)
	TArray<FString> ConversationMessage3;
};

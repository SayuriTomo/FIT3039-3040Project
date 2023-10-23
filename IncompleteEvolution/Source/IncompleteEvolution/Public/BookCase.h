// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BookPos.h"
#include "GameFramework/Actor.h"
#include "BookCase.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ABookCase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABookCase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UStaticMeshComponent* CaseLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UStaticMeshComponent* CaseMid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)UStaticMeshComponent* CaseRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)TArray<ABookPos*> BooksPos;
	
	bool bIsCompleted = false;
	bool bIsOperating = false;
	
	float CurrentTime;
	UPROPERTY(EditAnywhere)float TimeLimit = 4.0f;

	UPROPERTY(EditAnywhere,Category="Additional Attributes")
	USoundBase* Voice_DoorOpen;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

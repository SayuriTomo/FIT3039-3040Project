// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "Drink.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "VendingMachine.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AVendingMachine : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVendingMachine();

	UFUNCTION()
	virtual FString OnInteract();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category="SplineInfo")
	class USplineComponent* SplineComponent;

	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* TimelineComponent;
	
	UPROPERTY(EditAnywhere, Category="SplineInfo")
	class UCurveFloat* CurveFloat;
	
	UPROPERTY(EditAnywhere, Category="SplineInfo")
	class ADrink* Drink;
	
	UPROPERTY(EditAnywhere, Category = "Drink Can")
	TSubclassOf<class ADrink> DrinkClass;
	
	void DrinkFall();
	
	UPROPERTY(EditAnywhere, Category = "Drink Can")
	int CoinRequired;
	
	float TimeFalling = 0.f;

	UPROPERTY(EditAnywhere, Category = "Drink Can")
	float TimeFallingRequired = 5.0f;

	bool bIsDrinkFalling;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnTimelineTick(float Output);

};

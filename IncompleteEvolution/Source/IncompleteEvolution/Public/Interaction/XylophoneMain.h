// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XylophoneComponent.h"
#include "GameFramework/Actor.h"
#include "XylophoneMain.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API AXylophoneMain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXylophoneMain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<AXylophoneComponent*> ChildrenActors;

	float Time =0.5f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

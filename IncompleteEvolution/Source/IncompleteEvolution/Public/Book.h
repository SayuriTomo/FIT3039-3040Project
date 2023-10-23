// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorGrab.h"
#include "Book.generated.h"

/**
 * 
 */
UCLASS()
class INCOMPLETEEVOLUTION_API ABook : public AActorGrab
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)int BookNum;
};

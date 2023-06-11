// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "Engine/PostProcessVolume.h"
#include "IncompleteEvolution/IncompleteEvolutionCharacter.h"
#include "Carl.generated.h"

UCLASS()
class INCOMPLETEEVOLUTION_API ACarl : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarl();

	UFUNCTION()
	virtual FString OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainBody;

	FString Restart();
	TArray<FString> M_Restart={"What is it?","Restarting"};
	TArray<FString> C_Restart={"Player","???"};

	FString GetKey();
	TArray<FString> M_GetKey={
		"Hi,Ethan","Who are you","That's weird, but I amd Carl",
		"I am sure that we know each other", "...","So my name is Ethan","Sure",
		"Sorry, I don't remember anything","Oh, it must be the side effect","Side effect? What happened on me?",
		"Access restriction!","It seems I don't have permission to access this","There is a charging port in Power Supply Room.","It can help me get the permission",
		"But before going there, we need a key card","The card should be in Room 1","I will be waiting for you here","OK"
	};
	TArray<FString> C_GetKey={
		"? ? ?","Player","? ? ?",
		"Carl","Player","Ethan","Carl",
		"Ethan","Carl","Ethan",
		"Carl","Carl","Carl","Carl",
		"Carl","Carl","Carl","Ethan"
	};

	FString WhetherGetKey();
	TArray<FString> M_NotGetKey = {"It seems you don't get the key card","It should be in Room 1"};
	TArray<FString> C_NotGetKey ={"Carl", "Carl"};
	
	TArray<FString> M_HasGetKey = {"You got it!", "Now we need to go to Power Supply Room"};
	TArray<FString> C_HasGetKey ={"Carl","Carl"};
	
	TArray<FString> M_Charging = {
		"Reading---","Complete","OK, Ethan","I have got access to this level",
		"Let's move on","And I will explain what happened here",
		"By the way, do you remember Emily", "Emily? Who?","Ouch!","Experiment No.1001 start",
		"Who's there","Start recording","Ethan, can you hear me?","Start the injection"};
	TArray<FString> C_Charging ={
		"Carl", "Carl", "Carl", "Carl",
		"Carl", "Carl",
		"Carl","Ethan","Ethan","???",
		"Ethan","???","Carl","???"};

	FString ReadMessage(TArray<FString> Message,
		TArray<FString> Character,
		int Contact);

	void PlaySound(TArray<USoundBase*> Voice);
	UPROPERTY(EditAnywhere)
	FVector InvisibleLocation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	AIncompleteEvolutionCharacter* Player;
	
	int T_Contact = 0;
	bool IsTurn = false;
	int Index;
	FString Charging();
	void MovePPVolume();

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Voice_Restart;
	
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Voice_GetKey;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Voice_NotGetKey;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Voice_HasGetKey;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Voice_Charging;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APostProcessVolume* PP_WarpVolume;
	
};

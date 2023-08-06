// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "PhysicsHandle.h"
#include "ActorGrab.h"
#include "IncompleteEvolutionCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class AIncompleteEvolutionCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	class UPhysicsHandle* GrabHandle;
	
public:
	AIncompleteEvolutionCharacter();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

    // Single Grab System
	void SingleGrab();
	void ProcessSingleGrabHit(FHitResult& HitOut);
	bool SingleGrabActive;

	// Grab System
	void Grab();
	bool Trace(UWorld* World,TArray<AActor*>& ActorsToIgnore,
    			const FVector& Start,const FVector& End,
    			FHitResult& HitOut,ECollisionChannel CollisionChannel,bool ReturnPhysMat);
    void CallMyTrace(int Number);
	void ProcessGrabHit(FHitResult& HitOut);
	bool GrabActive;
	
	// Component Grab
	UPrimitiveComponent* HitComponentREF;
	UStaticMeshComponent* StaticMeshComponentREF;
	AActorGrab* HitActor;
	
	float OriginalDistance;
	FVector OriginalScale;

	// Component Scale
	void ProcessScaleHit(FHitResult& HitOut);
	float ClosestDistance = 50000;
	float CustomDistance = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Amount;

	// Section from Static Mesh
	TArray<FVector> VecticesList;
	TArray<int> TrianglesList;
	TArray<FVector> NormalsList;
	TArray<FVector2D> UVsList;
	TArray<FProcMeshTangent> TangentsList;
	FVector UnitDirection;

	// Interact System
	void Interact();
	void ProcessInteractHit(FHitResult& HitOut);

	void Fix();
	void ProcessFixHit(FHitResult& HitOut);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// Aim System
	bool AimGrab = false;
	bool AimInteract = false;
	void ProcessAimHit(FHitResult& HitOut);
	float AimTime = 0;
	const float AimTimeInterval = 10;
	
	FString InteractText;
	FString InteractCharacterName;
	AActor* InteractActor;
	
	
	UPROPERTY(BlueprintReadWrite)
	bool Interacting = false;
	bool InteractingEnd = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool WhetherGrab = false;
	bool WhetherScale = false;
	bool TargetUpdate;
	FString TaskText;

	UPROPERTY(EditAnywhere)
	bool GetKey=true;

	UPROPERTY(BlueprintReadWrite)
	bool AllowStand = true;

	UPROPERTY(BlueprintReadWrite)
	bool WhetherCrouch = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEnd = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsStart = true;
	void ReadPrologue();
	int Index=0;
	
	UPROPERTY(EditAnywhere)
	TArray<FString> M_Prologue = {"Hello Everyone!",
		"Today is exactly the 10-year anniversary",
		"of Compound 6 incident",
		"We should not forget its sorrow",
		"And this drug is still sold in the black market",
		"Therefore, if you contact with",
		"unnamed medicine",
		"Call the police quickly","Where is here?"};
	
	UPROPERTY(EditAnywhere)
	TArray<FString> C_Prologue ={"Media","Media","Media","Media","Media","Media","Media","Media","Player"};

	UPROPERTY(EditAnywhere)
	bool bIsGrabActive = false;

};


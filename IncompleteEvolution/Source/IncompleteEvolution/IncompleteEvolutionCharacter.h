// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
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

	// Grab System
	void Grab();
	bool Trace(UWorld* World,TArray<AActor*>& ActorsToIgnore,
    			const FVector& Start,const FVector& End,
    			FHitResult& HitOut,ECollisionChannel CollisionChannel,bool ReturnPhysMat);
    void CallMyTrace(int Number);
	void ProcessGrabHit(FHitResult& HitOut);
	
	
	
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
	void ProcessAimHit(FHitResult& HitOut);
	
	UPROPERTY(BlueprintReadWrite)
	bool WhetherGrab = false;
};

// Copyright Epic Games, Inc. All Rights Reserved.

#include "IncompleteEvolutionCharacter.h"
#include "IncompleteEvolutionProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"


//////////////////////////////////////////////////////////////////////////
// AIncompleteEvolutionCharacter

AIncompleteEvolutionCharacter::AIncompleteEvolutionCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
}

void AIncompleteEvolutionCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AIncompleteEvolutionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(WhetherGrab)
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
			StaticMeshComponentREF->GetStaticMesh(),0,0,
			VecticesList,TrianglesList,NormalsList,UVsList,
			TangentsList);
		UE_LOG(LogTemp,Warning,TEXT("VerticeList, %f"),VecticesList.Num());
		UE_LOG(LogTemp,Warning,TEXT("-------------------------------"));
		for(FVector Vectice:VecticesList)
		{
			FVector TempTransform = UKismetMathLibrary::TransformLocation(
				StaticMeshComponentREF->GetComponentTransform(),Vectice);
			UnitDirection = UKismetMathLibrary::GetDirectionUnitVector(
				FirstPersonCameraComponent->GetComponentLocation(),TempTransform);
			CallMyTrace(2);
		}
		
		if(HitComponentREF->GetComponentRotation().Roll>45.||
			HitComponentREF->GetComponentRotation().Roll<-45.||
			HitComponentREF->GetComponentRotation().Pitch>45.||
			HitComponentREF->GetComponentRotation().Pitch<-45.)
		{
			CustomDistance = 0.75;
		}
		else
		{
			CustomDistance = 0.95;
		}
		
		float DistanceMulti = ClosestDistance*CustomDistance;
		FVector TempUnitDirection = UKismetMathLibrary::GetDirectionUnitVector(
			GetFirstPersonCameraComponent()->GetComponentLocation(),
			HitComponentREF->GetComponentLocation());
 		FVector TempLerp = UKismetMathLibrary::VLerp(
 			TempUnitDirection,GetFirstPersonCameraComponent()->GetForwardVector(),
 			Amount);
		FVector TempLerpDistance = UKismetMathLibrary::Multiply_VectorFloat(
			TempLerp,DistanceMulti);
		HitComponentREF->SetWorldLocation(UKismetMathLibrary::Add_VectorVector(
			GetFirstPersonCameraComponent()->GetComponentLocation(),
			TempLerpDistance));

		float RatioCurOri = DistanceMulti/OriginalDistance;
		FVector ScaleChange= UKismetMathLibrary::Multiply_VectorFloat(
			OriginalScale,RatioCurOri);
		HitComponentREF->SetWorldScale3D(UKismetMathLibrary::ClampVectorSize(
			ScaleChange,0.1,50.));
		ClosestDistance = 50000;
		CustomDistance = 0;
	}
	else
	{
		CallMyTrace(3);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AIncompleteEvolutionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AIncompleteEvolutionCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AIncompleteEvolutionCharacter::Look);

		PlayerInputComponent->BindAction("Grab",IE_Pressed,this,&AIncompleteEvolutionCharacter::Grab);
	}
}


void AIncompleteEvolutionCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AIncompleteEvolutionCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (WhetherGrab)
		{
			AddControllerYawInput(LookAxisVector.X/3);
			AddControllerPitchInput(LookAxisVector.Y/3);
		}
		else
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void AIncompleteEvolutionCharacter::Grab()
{
	if(!WhetherGrab)
	{
		CallMyTrace(1);
	}
	else
	{
		HitComponentREF->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		HitComponentREF->SetSimulatePhysics(true);
		HitComponentREF->SetPhysicsLinearVelocity(FVector(0,0,0));
		HitComponentREF->SetPhysicsAngularVelocityInDegrees(FVector(0,0,0));
		WhetherGrab = false;
		ClosestDistance = 50000;
		HitActor->SetActorEnableCollision(true);
		HitActor->IsGrabbing = false;
		HitActor = nullptr;
	}
	
}

bool AIncompleteEvolutionCharacter::Trace(UWorld* World, TArray<AActor*>& ActorsToIgnore, const FVector& Start,
	const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel, bool ReturnPhysMat)
{
	if (!World)
	{
		return false;
	}
	
	FCollisionQueryParams TraceParams(FName(TEXT("My Trace")), true, ActorsToIgnore[0]);

	TraceParams.bTraceComplex = true;
	
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;
	
	TraceParams.AddIgnoredActors(ActorsToIgnore);

	const FName TraceTag("MyTraceTag");
	
	TraceParams.TraceTag = TraceTag;

	HitOut = FHitResult(ForceInit);
	
	World->LineTraceSingleByChannel (
		HitOut, //result
		Start, //start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
	);

	return (HitOut.GetActor() != NULL);
}

void AIncompleteEvolutionCharacter::CallMyTrace(int Number)
{
	const FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector ForwardVector;
	FVector End;
	
	if(Number == 1||Number == 3)
	{
		ForwardVector = GetFirstPersonCameraComponent()->GetForwardVector();
		End = Start + ForwardVector * 50000.f;
	}
	else if(Number==2)
	{
		ForwardVector = UnitDirection * 5000.f;
		End = Start + ForwardVector;
	}
	

	FHitResult HitData(ForceInit);
	
	TArray<AActor*> ActorsToIgnore;
	
	ActorsToIgnore.Add(this);
	
	if(Number==2)
	{
		ActorsToIgnore.Add(HitActor);
	}
	
	if (Trace(GetWorld(), ActorsToIgnore, Start, End, HitData, ECC_Visibility, false))
	{
		if (HitData.GetActor())
		{
			if(Number == 1)
			{
				ProcessGrabHit(HitData);
			}
			else if(Number == 2)
			{
				ProcessScaleHit(HitData);
			}
			else if(Number == 3)
			{
				ProcessAimHit(HitData);
			}
		} else
		{
			// The trace did not return an Actor
			// An error has occurred
			// Record a message in the error log
		}
	}
	else 
	{
		// We did not hit an Actor
	}
}

void AIncompleteEvolutionCharacter::ProcessGrabHit(FHitResult& HitOut)
{
	if(Cast<AActorGrab>(HitOut.GetActor()))
	{
		HitComponentREF = HitOut.GetComponent();
		HitComponentREF->SetSimulatePhysics(false);
		StaticMeshComponentREF = Cast<UStaticMeshComponent>(HitComponentREF);
		HitActor = Cast<AActorGrab>(HitOut.GetActor());
		HitActor->SetActorEnableCollision(false);
		HitActor->IsGrabbing = true;
		HitComponentREF->AttachToComponent(
			this->FirstPersonCameraComponent,FAttachmentTransformRules::KeepWorldTransform);
		WhetherGrab = true;
		OriginalDistance = UKismetMathLibrary::Vector_Distance(
			HitComponentREF->GetComponentLocation(),FirstPersonCameraComponent->GetComponentLocation());
		OriginalScale = HitComponentREF->GetComponentScale();
		
	}
}

void AIncompleteEvolutionCharacter::ProcessAimHit(FHitResult& HitOut)
{
	if(Cast<AActorGrab>(HitOut.GetActor()))
	{
		AimGrab = true;
	}
	else
	{
		AimGrab = false;
	}
}

void AIncompleteEvolutionCharacter::ProcessScaleHit(FHitResult& HitOut)
{
	if(HitOut.GetActor())
	{
		float CurDistance = UKismetMathLibrary::Vector_Distance(
			FirstPersonCameraComponent->GetComponentLocation(),
			HitOut.ImpactPoint);
		if(CurDistance<ClosestDistance)
		{
			ClosestDistance = CurDistance;
		}
	}
}

void AIncompleteEvolutionCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AIncompleteEvolutionCharacter::GetHasRifle()
{
	return bHasRifle;
}
// Copyright Epic Games, Inc. All Rights Reserved.

#include "IncompleteEvolutionCharacter.h"
#include "IncompleteEvolutionProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InteractInterface.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Windows/LiveCoding/Private/External/LC_HeartBeat.h"


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

	GrabHandle = CreateDefaultSubobject<UPhysicsHandle>(TEXT("Grab Handle"));
	
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

	Interacting = true;
	ReadPrologue();
	


}

void AIncompleteEvolutionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(WhetherGrab)
	{
		if(WhetherScale)
		{
			UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
				StaticMeshComponentREF->GetStaticMesh(),0,0,
				VecticesList,TrianglesList,NormalsList,UVsList,
				TangentsList);
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
			const FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
			FVector ForwardVector = GetFirstPersonCameraComponent()->GetForwardVector();
			FVector End = Start + ForwardVector * 250.f;
			GrabHandle->SetTargetLocation(End);
		}
	}
	else
	{
		if(AimTime>=AimTimeInterval)
		{
			CallMyTrace(3);
			AimTime=0;
		}
		else
		{
			AimTime += 1;
		}
		
	}

	
}

//////////////////////////////////////////////////////////////////////////// Input

void AIncompleteEvolutionCharacter::Interact()
{
	if(!Interacting)
	{
		CallMyTrace(4);
	}
	else
	{
		if(InteractingEnd)
		{
			Interacting = false;
			InteractingEnd= false;
			InteractActor= nullptr;
		}
		else
		{
			if(bIsStart)
			{
				ReadPrologue();
			}
			else
			{
				if(InteractActor)
				{
					InteractText = Cast<IInteractInterface>(InteractActor)->OnInteract();
				}
			}
		}
	}
}

void AIncompleteEvolutionCharacter::ProcessInteractHit(FHitResult& HitOut)
{
	if(IInteractInterface* ActorCheck = Cast<IInteractInterface>(HitOut.GetActor()))
	{
		Interacting = true;
		InteractText = ActorCheck->OnInteract();
		InteractActor = HitOut.GetActor();
	}
}

void AIncompleteEvolutionCharacter::Fix()
{
	CallMyTrace(6);
}

void AIncompleteEvolutionCharacter::ProcessFixHit(FHitResult& HitOut)
{
	if(!WhetherGrab)
	{
		if(Cast<AActorGrab>(HitOut.GetActor()))
		{
			if(Cast<AActorGrab>(HitOut.GetActor())->IsFixing)
			{
				Cast<AActorGrab>(HitOut.GetActor())->IsFixing = false;
			}
			else
			{
				Cast<AActorGrab>(HitOut.GetActor())->IsFixing = true;
			}
		}
	}
}

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
		PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&AIncompleteEvolutionCharacter::Interact);
		PlayerInputComponent->BindAction("SingleGrab",IE_Pressed,this,&AIncompleteEvolutionCharacter::SingleGrab);
		PlayerInputComponent->BindAction("Fix",IE_Pressed,this,&AIncompleteEvolutionCharacter::Fix);
	}
}


void AIncompleteEvolutionCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if(!Interacting)
	{
		if (Controller != nullptr)
		{
			// add movement 
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
}

void AIncompleteEvolutionCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X/2);
		AddControllerPitchInput(LookAxisVector.Y/2);
	}
}

void AIncompleteEvolutionCharacter::SingleGrab()
{
	if(!WhetherGrab&&!GrabActive)
	{
		CallMyTrace(5);
	}
	else
	{
		if(SingleGrabActive)
		{
			GrabHandle->ReleaseComponent();
			HitActor->IsGrabbing = false;
			HitActor = nullptr;
			WhetherGrab = false;
			SingleGrabActive =false;
		}
	}
}

void AIncompleteEvolutionCharacter::ProcessSingleGrabHit(FHitResult& HitOut)
{
	if(Cast<AActorGrab>(HitOut.GetActor()))
	{
		if(!Cast<AActorGrab>(HitOut.GetActor())->IsFixing)
		{
			GrabHandle ->GrabComponentAtLocationWithRotation(HitOut.GetComponent(),HitOut.BoneName,
				HitOut.GetActor()->GetActorLocation(),FRotator(0,0,0));
			WhetherGrab = true;
			HitActor = Cast<AActorGrab>(HitOut.GetActor());
			HitActor->IsGrabbing = true;
			SingleGrabActive = true;
		}
	}
}

void AIncompleteEvolutionCharacter::Grab()
{
	if(!WhetherGrab&&!SingleGrabActive)
	{
		CallMyTrace(1);
	}
	else
	{
		if(GrabActive)
		{
			HitComponentREF->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			HitComponentREF->SetSimulatePhysics(true);
			HitComponentREF->SetPhysicsLinearVelocity(FVector(0,0,0));
			HitComponentREF->SetPhysicsAngularVelocityInDegrees(FVector(0,0,0));
			WhetherGrab = false;
			WhetherScale = false;
			ClosestDistance = 50000;
			HitActor->SetActorEnableCollision(true);
			HitActor->IsGrabbing = false;
			HitActor = nullptr;
			GrabActive = false;
		}
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
	
	switch (Number) {
		case 2:
			{
				ForwardVector = UnitDirection * 5000.f;End = Start + ForwardVector;
				break;
			}
		default:
			{
				ForwardVector = GetFirstPersonCameraComponent()->GetForwardVector();
				End = Start + ForwardVector * 1000.f;
				break;
			}
	}
	/*
	if(Number == 1||Number == 3||Number == 4||Number == 5||Number==6)
	{
		ForwardVector = GetFirstPersonCameraComponent()->GetForwardVector();
		End = Start + ForwardVector * 1000.f;
	}
	else if(Number == 2)
	{
		ForwardVector = UnitDirection * 5000.f;
		End = Start + ForwardVector;
	}
	*/
	
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
			switch (Number)
			{
				case 1:
					{
						ProcessGrabHit(HitData);
						break;
					}
				case 2:
					{
						ProcessScaleHit(HitData);
						break;
					}
				case 3:
					{
						ProcessAimHit(HitData);
						break;
					}
				case 4:
					{
						ProcessInteractHit(HitData);
						break;
					}
				case 5:{ProcessSingleGrabHit(HitData);
						break;}
				case 6:
					{
						ProcessFixHit(HitData);
						break;
					}
				default:{}
			}
			
			/*
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
			else if(Number == 4)
			{
				ProcessInteractHit(HitData);
			}
			else if(Number == 5)
			{
				ProcessSingleGrabHit(HitData);
			}
			else if(Number ==6)
			{
				ProcessFixHit(HitData);
			}*/
			
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
		AimGrab=false;
		AimInteract=false;
	}
}

void AIncompleteEvolutionCharacter::ProcessGrabHit(FHitResult& HitOut)
{
	if(Cast<AActorGrab>(HitOut.GetActor()))
	{
		if(!Cast<AActorGrab>(HitOut.GetActor())->IsFixing)
		{
			GrabActive = true;
			HitComponentREF = HitOut.GetComponent();
			HitComponentREF->SetSimulatePhysics(false);
			StaticMeshComponentREF = Cast<UStaticMeshComponent>(HitComponentREF);
			HitActor = Cast<AActorGrab>(HitOut.GetActor());
		
			WhetherGrab = true;
			WhetherScale = true;
		
			HitActor->IsGrabbing = true;
			HitActor->SetActorEnableCollision(false);
		
			HitComponentREF->AttachToComponent(
				this->FirstPersonCameraComponent,FAttachmentTransformRules::KeepWorldTransform);
			OriginalDistance = UKismetMathLibrary::Vector_Distance(
				HitComponentREF->GetComponentLocation(),FirstPersonCameraComponent->GetComponentLocation());
			OriginalScale = HitComponentREF->GetComponentScale();
		}
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
	
	if(Cast<IInteractInterface>(HitOut.GetActor()))
	{
		AimInteract = true;
	}
	else
	{
		AimInteract = false;
	}
	
	
}

void AIncompleteEvolutionCharacter::ReadPrologue()
{
	if(Index<M_Prologue.Num())
	{
		InteractCharacterName = C_Prologue[Index];
		InteractText = M_Prologue[Index];
		Index += 1;
		if(Index == M_Prologue.Num())
		{
			Index = 0;
			bIsStart = false;
			InteractingEnd = true;
			TargetUpdate = true;
			TaskText = "1. Leave Room";
		}
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
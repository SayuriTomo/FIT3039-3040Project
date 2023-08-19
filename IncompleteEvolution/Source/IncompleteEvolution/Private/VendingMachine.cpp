// Fill out your copyright notice in the Description page of Project Settings.


#include "VendingMachine.h"



// Sets default values
AVendingMachine::AVendingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main body"));
	MainBody->SetupAttachment(RootComponent);
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SplineComponent->SetupAttachment(MainBody);

	static ConstructorHelpers::FObjectFinder<UBlueprint> DrinkBlueprint(TEXT("Blueprint'/Game/FIT3039-3040Project/Blueprints/ActorGrab/BP_Drink.BP_Drink'"));
	if (DrinkBlueprint.Object){
		DrinkClass = DrinkBlueprint.Object->GeneratedClass;
	}

}

FString AVendingMachine::OnInteract()
{
	FString InteractMessage;
	AIncompleteEvolutionCharacter* Player =
			Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->Interacting = false;
	FVector SpawnLocation = this->GetActorLocation();
	Drink = (ADrink*) GetWorld()->SpawnActor(DrinkClass, &SpawnLocation);
	DrinkFall();
	return  InteractMessage;
}


void AVendingMachine::OnTimelineTick(float Output)
{
	float CurDistance = SplineComponent->GetSplineLength()*Output;
	FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(CurDistance,ESplineCoordinateSpace::World);
	FRotator NewRotation = SplineComponent->GetRotationAtDistanceAlongSpline(CurDistance,ESplineCoordinateSpace::World);
	if(Drink!=nullptr)
	{
		Drink->SetActorLocationAndRotation(NewLocation,NewRotation);
	}
}

// Called when the game starts or when spawned
void AVendingMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVendingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TimelineComponent!=nullptr)
	{
		TimelineComponent->TickComponent(DeltaTime,ELevelTick::LEVELTICK_TimeOnly,NULL);
	}
}

void AVendingMachine::DrinkFall()
{
	
	if(CurveFloat!=nullptr)
	{
		TimelineComponent = NewObject<UTimelineComponent>(this,TEXT("Timeline Component"));
		FOnTimelineFloat TimelineEvent;
		TimelineEvent.BindUFunction(this,TEXT("OnTimelineTick"));
		TimelineComponent->AddInterpFloat(CurveFloat,TimelineEvent);
		TimelineComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
		TimelineComponent->SetTimelineLength(5.0f);

		TimelineComponent->PlayFromStart();
		TimelineComponent->RegisterComponent();
	}
}



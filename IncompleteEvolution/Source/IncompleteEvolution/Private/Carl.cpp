// Fill out your copyright notice in the Description page of Project Settings.


#include "Carl.h"


// Sets default values
ACarl::ACarl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	MainBody->SetupAttachment(RootComponent);
}

FString ACarl::OnInteract()
{
	FString InteractMessage;
	if(!IsTurn)
	{
		return Restart();
	}
	else
	{
		if(T_Contact == 1)
		{
			return GetKey();
		}
		else if(T_Contact==2)
		{
			return WhetherGetKey();
		}
	}
	return InteractMessage;
}


FString ACarl::Restart()
{
	return ReadMessage(M_Restart,C_Restart,T_Contact);
}

FString ACarl::GetKey()
{
	FString InteractMessage = ReadMessage(M_GetKey,C_GetKey,T_Contact);
	Player->TargetUpdate = true;
	return InteractMessage;
}

FString ACarl::WhetherGetKey()
{
	FString InteractMessage;
	if(!Player->GetKey)
	{
		 return ReadMessage(M_NotGetKey,C_NotGetKey,T_Contact);
	}
	else
	{
		return ReadMessage(M_HasGetKey,C_HasGetKey,T_Contact);
	}
}

FString ACarl::ReadMessage(TArray<FString> Message, TArray<FString> Character,int Contact)
{
	FString InteractMessage;
	if(Index<Message.Num())
	{
		Player->InteractCharacterName = Character[Index];
		InteractMessage = Message[Index];
		Index += 1;
		if(Index == Message.Num())
		{
			Index = 0;
			Player->InteractingEnd = true;
			if(Contact==0)
			{
				IsTurn = true;
				T_Contact +=1;
			}
			else if(Contact==1)
			{
				Player->TargetUpdate = true;
				Player->TaskText = "3. Find the Key card";
				T_Contact +=1;
			}
			else if(Contact==2)
			{
				if(Player->GetKey)
				{
					Player->TargetUpdate = true;
					Player->TaskText = "4. Go to Power Supply Room";
					T_Contact +=1;
					SetActorLocation(InvisibleLocation);
				}
			}
			
		}
	}
	return InteractMessage;
}

// Called when the game starts or when spawned
void ACarl::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AIncompleteEvolutionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ACarl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


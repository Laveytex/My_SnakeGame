// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "HoverComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	HoverComponent = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverComponent"));
	
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::Interact(AActor* Interactor,bool bIsHead)
{
	if(bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if(IsValid(Snake))
		{
			Snake->AddSnakeElement();
			Snake->Score=Snake->Score+10;
			UE_LOG(LogTemp, Warning, TEXT("Score: %f"), Snake->Score);
		}
		float RandomX = FMath::FRandRange(-254,254);
		float RandomY = FMath::FRandRange(-254,254);
		FVector NewLocation = FVector(RandomX,RandomY,0);
		GetWorld()->SpawnActor<AFood>(FoodClass,NewLocation, FRotator(0));
		this->Destroy();
	}
}



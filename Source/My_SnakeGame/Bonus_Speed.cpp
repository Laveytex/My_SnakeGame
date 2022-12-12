// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus_Speed.h"
#include "SnakeBase.h"
#include "HoverComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ABonus_Speed::ABonus_Speed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	HoverComponent = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverComponent"));
}

// Called when the game starts or when spawned
void ABonus_Speed::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABonus_Speed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABonus_Speed::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if(IsValid(Snake))
	{
		float PrevMovementSpeed = Snake->MovementSpeed;
		float NewMovementSpeed = Snake->MovementSpeed /BonusMovementSpeed;
		Snake->SetActorTickInterval(NewMovementSpeed);
		FTimerHandle TimerSpeedBrakerHandle;
		//GetWorld()->GetTimerManager().SetTimer(TimerSpeedBrakerHandle, this, &ABonus_Speed::SpeedChange(PrevMovementSpeed, Snake), 5.0f, false);
	}
	this->Destroy();
}

void ABonus_Speed::SpeedChange(float Value, ASnakeBase* Other)
{
	Other->SetActorTickInterval(Value);
}


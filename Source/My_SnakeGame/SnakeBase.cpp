// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include <string>
#include "Engine/Engine.h"
#include "SnakeElementBase.h"
#include "Interacteble.h"



// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	LastMoveDirection = EMovementDirection::UP;
	MovementSpeed = 0.3f;
	Score = 0;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);
	//Score = 0;
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	if(GEngine)
	{
		FString DebugMsgScore = FString::Printf(TEXT("Score: %s"), *FString::SanitizeFloat(Score));
		GEngine->AddOnScreenDebugMessage(-1,0.4,FColor::Blue,DebugMsgScore);
	}
}

void ASnakeBase::AddSnakeElement(int ElementNum)
{
	for (int i=0; i<ElementNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num()*ElementSize,0,0);
		FTransform NewTransform(GetActorLocation()-NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass,NewTransform);
		NewSnakeElem->MeshComponent->SetVisibility(false);
		NewSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if(ElemIndex==0)
		{
			NewSnakeElem->SetFirstElementType();
			NewSnakeElem->MeshComponent->SetVisibility(true);
		}
	}
}

void ASnakeBase::Move()
{

	FVector MovementVector(ForceInitToZero);
	float MovementSpeedSize = ElementSize;
	
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X+=MovementSpeedSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X-=MovementSpeedSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y-=MovementSpeedSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y+=MovementSpeedSize;
		break;
	}
	
	
	SnakeElements[0]->ToggleCollision();
	
	for (int i=SnakeElements.Num()-1;i>0;--i)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i-1];
		FVector PrevLocation=PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
		CurrentElement->MeshComponent->SetVisibility(true);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	bIsSetMove = false;
	
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if(IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex==0;
		IInteracteble* InteractebleInterface = Cast<IInteracteble>(Other);
		if(InteractebleInterface)
		{
			InteractebleInterface->Interact(this, bIsFirst);
		}
	}
	
}


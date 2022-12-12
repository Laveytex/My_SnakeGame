// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interacteble.h"



// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	LastMoveDirection = EMovementDirection::UP;
	MovementSpeed = 20.f;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementNum)
{
	for (int i=0; i<ElementNum; i++)
	{
		FVector NewLocation(SnakeElements.Num()*ElementSize,0,0);
		FTransform NewTransform(GetActorLocation()-NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass,NewTransform);
		NewSnakeElem->SnakeOwner = this;
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if(ElemIndex==0)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetFirstElemType"));
			NewSnakeElem->SetFirstElementType();
		}
		UE_LOG(LogTemp, Warning, TEXT("ElementAdded"));
	}
	
	UE_LOG(LogTemp, Warning, TEXT("ElemNum: %d"), SnakeElements.Num());
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
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	bIsSetMove = false;
	
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("SnakeElementOverlap"));
	
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


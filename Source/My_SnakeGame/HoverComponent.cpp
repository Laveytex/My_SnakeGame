// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverComponent.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SnakeOwner = GetOwner();
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = SnakeOwner->GetActorLocation();
	StartRotation = SnakeOwner->GetActorRotation();
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//y = [amplitude] * sin ( ( [frequency] * x ) – [phase] )
	if(SnakeOwner)
	{
		FVector NewLocation = StartPosition;
		FRotator NewRotation = StartRotation;
		
		float DeltaHeight = Amplitude*FMath::Sin(Frequency*(RunnningTime+DeltaTime))-Phase;
		NewLocation.Z= DeltaHeight;
		
		
		float DeltaRotation = (DeltaTime+RunnningTime) * RotationValue;
		NewRotation.Yaw += DeltaRotation;
		
		RunnningTime += DeltaTime;
		
		SnakeOwner->SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}


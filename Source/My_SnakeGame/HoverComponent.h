// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MY_SNAKEGAME_API UHoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover Parameters")
	float Frequency=2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover Parameters")
	float Amplitude=10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover Parameters")
	float Phase=0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover Parameters")
	float RotationValue=5;
	
	//UPROPERTY(VisibleAnywhere, Category = "Hover Parameters")
	FVector StartPosition;
	FRotator StartRotation;
	
	float RunnningTime;
	
	AActor* SnakeOwner = GetOwner();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

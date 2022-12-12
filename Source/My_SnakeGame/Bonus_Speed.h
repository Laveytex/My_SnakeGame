// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interacteble.h"
#include "SnakeBase.h"
#include "GameFramework/Actor.h"
#include "Bonus_Speed.generated.h"

class  UStaticMeshComponent;
class  UHoverComponent;

UCLASS()
class MY_SNAKEGAME_API ABonus_Speed : public AActor, public IInteracteble
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus_Speed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	float BonusMovementSpeed = 4;

	UHoverComponent* HoverComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	void SpeedChange(float Value, ASnakeBase* Other);
};

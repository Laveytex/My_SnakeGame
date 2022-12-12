// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interacteble.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

class UStaticMeshComponent;

UCLASS()
class MY_SNAKEGAME_API AWall : public AActor, public IInteracteble
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
virtual void Interact(AActor* Interactor, bool bIsHead) override;
};

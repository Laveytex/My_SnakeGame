// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interacteble.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"


class UStaticMeshComponent;
class UHoverComponent;

UCLASS()
class MY_SNAKEGAME_API AFood : public AActor, public IInteracteble
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UHoverComponent* HoverComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};

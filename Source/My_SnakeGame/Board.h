// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class UStaticMesh;
class AWall;

UCLASS()
class MY_SNAKEGAME_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();
	UPROPERTY()
	float BoardSize;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWall> WallClass;

	UPROPERTY(EditAnywhere)
	float WallDistants;

	UPROPERTY()
	TArray<AWall*> WallElements;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnFloor (int WallElementNum);
	void SpawnBorder (int WallElementNum);
};




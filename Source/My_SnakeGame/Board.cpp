// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Wall.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	int WallElementNum = 10;
	SpawnFloor(WallElementNum);
	SpawnBorder(WallElementNum);
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABoard::SpawnFloor(int WallElementNum)
{
	
	for(int i=-WallElementNum;i<WallElementNum;i++)
	{
		for(int j=-WallElementNum;j<WallElementNum;j++)
		{
			float Random = FMath::FRandRange(0,100);
			//Create Floor
			if(Random>5)
			{
				FVector NewLocation = FVector(i*WallDistants,j*WallDistants,-30);
				AWall* NewWallElement = GetWorld()->SpawnActor<AWall>(WallClass,NewLocation,FRotator());
				NewWallElement->SetActorRelativeScale3D(FVector(0.3));
				WallElements.Add(NewWallElement);
			}
			//Create Wall
			else if(Random<5&&Random>2)
			{
				FVector NewLocation = FVector(i*WallDistants,j*WallDistants,0);
				AWall* NewWallElement = GetWorld()->SpawnActor<AWall>(WallClass,NewLocation,FRotator());
				FVector NewLocation2 = FVector(i*WallDistants,j*WallDistants,-30);
				AWall* NewWallElement2 = GetWorld()->SpawnActor<AWall>(WallClass,NewLocation2,FRotator());
				NewWallElement->SetActorRelativeScale3D(FVector(0.29));
				WallElements.Add(NewWallElement);
			}
			//Create Hole
			else if(Random<2)
			{
				FVector NewLocation = FVector(i*WallDistants,j*WallDistants,0);
				AWall* NewWallElement = GetWorld()->SpawnActor<AWall>(WallClass,NewLocation,FRotator());
				NewWallElement->SetActorRelativeScale3D(FVector(0.29));
				NewWallElement->MeshComponent->SetVisibility(false);
				WallElements.Add(NewWallElement);
			}
		}
	}
}

void ABoard::SpawnBorder(int WallElementNum)
{
	for(int i=-WallElementNum;i<WallElementNum;i++)
	{
		
		for(int j=-WallElementNum;j<WallElementNum;j++)
		{
			if(i==WallElementNum-1||i==-WallElementNum||j==-WallElementNum||j==WallElementNum-1)
			{
				FVector NewLocation = FVector(i*WallDistants,j*WallDistants,0);
				AWall* NewWallElement = GetWorld()->SpawnActor<AWall>(WallClass,NewLocation,FRotator());
				NewWallElement->SetActorRelativeScale3D(FVector(0.3));
			}
		}
	}
}


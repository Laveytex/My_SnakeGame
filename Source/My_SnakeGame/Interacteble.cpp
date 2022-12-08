// Fill out your copyright notice in the Description page of Project Settings.


#include "Interacteble.h"

// Add default functionality here for any IInteracteble functions that are not pure virtual.
void IInteracteble::Interact(AActor* Interactor, bool BIshead)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
}

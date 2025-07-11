// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableMaster.h"

#include "GameFramework/Character.h"

AInteractableMaster::AInteractableMaster(): InteractSound(nullptr), ItemMeshComponent(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMeshComponent;
	ItemMeshComponent->SetSimulatePhysics(false);
	ItemMeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
}

bool AInteractableMaster::CanInteract(ACharacter* Character)
{
	if (!IsValid(Character))
	{
		return false;
	}
	
	return true;
}

void AInteractableMaster::Interaction(ACharacter* Character, UInventoryComponent* InventoryComponent)
{
	if (!CanInteract(Character))
	{
		return;
	}
}
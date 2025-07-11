// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryMachineMaster.h"

#include "InventorySystem/InventoryComponent.h"
#include "TheAutomator/Public/DebugUtils.h"


// Sets default values
AFactoryMachineMaster::AFactoryMachineMaster(): InputInventory(nullptr), RecipeAsset(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AFactoryMachineMaster::ReceiveItem(FName ItemID, int32 Quantity)
{
	if (!InputInventory)
		return false;

	bool bSuccess = InputInventory->AddItem(ItemID, Quantity);
	if (bSuccess)
	{
		DEBUG_WARN("Item Succesfully added to Machine");
	}

	return bSuccess;
}

// Called when the game starts or when spawned
void AFactoryMachineMaster::BeginPlay()
{
	Super::BeginPlay();
	
}




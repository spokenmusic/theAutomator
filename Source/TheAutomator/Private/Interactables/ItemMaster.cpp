// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMaster.h"

#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/ItemData.h"
#include "InventorySystem/ItemDataSubsystem.h"
#include "Subsystems/PlayerStatsSubsystem.h"
#include "TheAutomator/Public/DebugUtils.h"

// Sets default values
AItemMaster::AItemMaster(): ItemQuantity(0), ItemMeshScale(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AItemMaster::BeginPlay()
{
	Super::BeginPlay();

	UItemDataSubsystem* Sub = UItemDataSubsystem::GetItemDataSubsystem(this);

	FItemData ItemData = Sub->GetItemDefinition(ItemID);
	if (ItemData.ItemID != NAME_None)
	{
		if (ItemMeshComponent && ItemData.ItemMesh)
		{
			ItemMeshComponent->SetStaticMesh(ItemData.ItemMesh);
			FVector NewScale(ItemData.ItemMeshScale);
			ItemMeshComponent->SetRelativeScale3D(NewScale);
		}
		
		ItemMeshScale  = ItemData.ItemMeshScale;
		InteractSound  = ItemData.PickupSound;
		ItemName       = ItemData.DisplayName;
	}
	else
	{
		DEBUG_ERROR("Invalid ItemID: %s", *ItemID.ToString());
	}
}

void AItemMaster::Interaction(ACharacter* Character, UInventoryComponent* InventoryComponent)
{
	Super::Interaction(Character, InventoryComponent);

	if (InventoryComponent)
	{
		if (InventoryComponent->AddItem(ItemID, ItemQuantity))
		{
			if (UPlayerStatsSubsystem* Stats = UPlayerStatsSubsystem::GetPlayerStatsSubsystem(this))
			{
				Stats->IncrementStat(FName(*(FString(TEXT("Picked_")) + ItemID.ToString())), ItemQuantity);
			}
			
			DEBUG_INFO("ItemName: %s, Quantity: %d added to player inventory", *ItemName.ToString(), ItemQuantity);
			Destroy();
		}
		else
		{
			// Todo: Call the HUD component and send a message telling ItemName and why it couldn't be picked up.
			DEBUG_WARN("Failed to add item to inventory");
		}
	}
}

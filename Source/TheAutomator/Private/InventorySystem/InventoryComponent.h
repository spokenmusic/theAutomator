#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct THEAUTOMATOR_API FInventorySlot
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHotkeyAssigned;

	FInventorySlot()
		: ItemID(NAME_None), Count(0), IsHotkeyAssigned(false)
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEAUTOMATOR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	/** Adds Quantity of ItemID. Returns true if all were added. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItem(FName ItemID, int32 Quantity);

	/** Removes up to Quantity of ItemID. Returns true if all removed. */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItem(FName ItemID, int32 Quantity);

	/** Gets total count of ItemID in inventory */
	UFUNCTION(BlueprintPure, Category="Inventory")
	int32 GetItemCount(FName ItemID) const;

	/** Returns whether there's space for Quantity of ItemID */
	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasSpaceFor(FName ItemID, int32 Quantity) const;

	/** Exposes raw slots array to Blueprints */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	const TArray<FInventorySlot>& GetSlots() const;

	/** Swaps or merges two slots; returns true on anything changed */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool MoveItem(int32 FromIndex, int32 ToIndex);

	/** Finds and returns the item definition for a given ItemID */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	FItemData GetItemDefinition(FName ItemID) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 GetCapacity() const { return Capacity; }

	/** Inventory change broadcast */
	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	// HOTKEYS //
	/** Assigns whatever is in Slots[SlotIndex] to the hotbar at HotbarIndex */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AssignHotkey(int32 SlotIndex, int32 HotbarIndex);

	/** Clears the hotkey at HotbarIndex */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool UnassignHotkey(int32 HotbarIndex);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	UDataTable* ItemDataTable;

	/** Inventory slots */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TArray<FInventorySlot> Slots;

	/** Fixed‐size hotbar: each entry is an ItemID or NAME_None */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
	TArray<FName> HotbarSlots;

	/** Maximum number of different slots */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(ClampMin=1))
	int32 Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory", meta=(ClampMin=1))
	int32 HotbarSize = 8;

	virtual void BeginPlay() override;

private:
	/** Finds item definition row by matching ItemID field */
	const struct FItemData* FindItemDef(FName ItemID) const;
};



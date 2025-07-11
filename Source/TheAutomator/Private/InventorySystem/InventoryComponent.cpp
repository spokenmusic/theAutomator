#include "InventoryComponent.h"

#include "ItemData.h"
#include "Engine/World.h"

UInventoryComponent::UInventoryComponent(): ItemDataTable(nullptr)
{
    PrimaryComponentTick.bCanEverTick = false;
    Capacity = 20;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    Slots.SetNum(Capacity);
    HotbarSlots.Init(NAME_None, HotbarSize);
}

const TArray<FInventorySlot>& UInventoryComponent::GetSlots() const
{
    return Slots;
}

bool UInventoryComponent::MoveItem(int32 FromIndex, int32 ToIndex)
{
    // Validate indices
    if (!Slots.IsValidIndex(FromIndex) || !Slots.IsValidIndex(ToIndex) || FromIndex == ToIndex)
        return false;

    FInventorySlot& Src = Slots[FromIndex];
    FInventorySlot& Dst = Slots[ToIndex];

    // If either is empty, just swap
    if (Src.ItemID.IsNone() || Dst.ItemID.IsNone())
    {
        Slots.Swap(FromIndex, ToIndex);
        OnInventoryUpdated.Broadcast();
        return true;
    }

    // If same ItemID and stacking is possible, merge
    if (Src.ItemID == Dst.ItemID)
    {
        FItemData Def = GetItemDefinition(Src.ItemID);
        int32 MaxStack = Def.MaxStackSize;
        int32 Space = MaxStack - Dst.Count;
        if (Space > 0)
        {
            int32 ToMove = FMath::Min(Src.Count, Space);
            Dst.Count += ToMove;
            Src.Count -= ToMove;
            if (Src.Count == 0)
                Src.ItemID = NAME_None;
            OnInventoryUpdated.Broadcast();
            return true;
        }
    }

    // Otherwise, do a straight swap
    Slots.Swap(FromIndex, ToIndex);
    OnInventoryUpdated.Broadcast();
    return true;
}

bool UInventoryComponent::AssignHotkey(int32 SlotIndex, int32 HotbarIndex)
{
    if (!Slots.IsValidIndex(SlotIndex) || !HotbarSlots.IsValidIndex(HotbarIndex))
        return false;

    const FInventorySlot& Slot = Slots[SlotIndex];
    if (Slot.ItemID.IsNone() || Slot.Count == 0)
        return false;

    HotbarSlots[HotbarIndex] = Slot.ItemID;
    OnInventoryUpdated.Broadcast();
    return true;
}

bool UInventoryComponent::UnassignHotkey(int32 HotbarIndex)
{
    // Only validate the hotbar array
    if (!HotbarSlots.IsValidIndex(HotbarIndex))
        return false;

    // Clear that hotbar slot
    HotbarSlots[HotbarIndex] = NAME_None;

    OnInventoryUpdated.Broadcast();
    return true;
}


FItemData UInventoryComponent::GetItemDefinition(FName ItemID) const
{
    const FItemData* Def = FindItemDef(ItemID);
    if (Def)
    {
        return *Def;
    }
    return FItemData(); // Return empty default
}

const FItemData* UInventoryComponent::FindItemDef(FName ItemID) const
{
    if (!ItemDataTable)
        return nullptr;

    for (const auto& Pair : ItemDataTable->GetRowMap())
    {
        const FItemData* RowData = reinterpret_cast<const FItemData*>(Pair.Value);
        if (RowData && RowData->ItemID == ItemID)
        {
            return RowData;
        }
    }
    return nullptr;
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Quantity)
{
    if (Quantity <= 0)
        return false;

    FItemData Def = GetItemDefinition(ItemID);
    if (Def.ItemID.IsNone())
        return false;

    int32 Remaining = Quantity;
    int32 MaxStack = Def.MaxStackSize;

    for (FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID && Slot.Count < MaxStack)
        {
            int32 ToAdd = FMath::Min(MaxStack - Slot.Count, Remaining);
            Slot.Count += ToAdd;
            Remaining -= ToAdd;
            if (Remaining <= 0)
            {
                OnInventoryUpdated.Broadcast();
                return true;
            }
        }
    }

    for (FInventorySlot& Slot : Slots)
    {
        if (Remaining <= 0)
            break;

        if (Slot.ItemID == NAME_None || Slot.Count == 0)
        {
            int32 ToAdd = FMath::Min(MaxStack, Remaining);
            Slot.ItemID = ItemID;
            Slot.Count = ToAdd;
            Remaining -= ToAdd;
        }
    }

    if (Remaining == 0)
    {
        OnInventoryUpdated.Broadcast();
        return true;
    }
    return false;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Quantity)
{
    if (Quantity <= 0)
        return false;

    int32 Remaining = Quantity;
    for (FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID && Slot.Count > 0)
        {
            int32 ToRemove = FMath::Min(Slot.Count, Remaining);
            Slot.Count -= ToRemove;
            Remaining -= ToRemove;
            if (Slot.Count == 0)
                Slot.ItemID = NAME_None;
            if (Remaining <= 0)
            {
                OnInventoryUpdated.Broadcast();
                return true;
            }
        }
    }
    return false;
}

int32 UInventoryComponent::GetItemCount(FName ItemID) const
{
    int32 Total = 0;
    for (const FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID)
            Total += Slot.Count;
    }
    return Total;
}

bool UInventoryComponent::HasSpaceFor(FName ItemID, int32 Quantity) const
{
    if (Quantity <= 0)
        return false;

    FItemData Def = GetItemDefinition(ItemID);
    if (Def.ItemID.IsNone())
        return false;

    int32 Remaining = Quantity;
    int32 MaxStack = Def.MaxStackSize;

    for (const FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID)
        {
            Remaining -= (MaxStack - Slot.Count);
            if (Remaining <= 0)
                return true;
        }
    }

    int32 EmptySlots = 0;
    for (const FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == NAME_None || Slot.Count == 0)
            ++EmptySlots;
    }

    Remaining -= EmptySlots * MaxStack;
    return Remaining <= 0;
}

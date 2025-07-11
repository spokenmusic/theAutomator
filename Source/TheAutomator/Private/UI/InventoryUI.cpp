// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUI.h"

#include "InventorySlotUI.h"
#include "Components/UniformGridPanel.h"
#include "InventorySystem/InventoryComponent.h"


void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
	// do nothing until Initialize
}

void UInventoryUI::Initialize(UInventoryComponent* InvComp)
{
	if (!InvComp || !SlotGrid || !SlotWidgetClass)
	{
		return;
	}
	InventoryComp = InvComp;

	// Create slot pool
	int32 Capacity = InventoryComp->GetSlots().Num();
	SlotWidgets.Reserve(Capacity);
	for (int32 Index = 0; Index < Capacity; ++Index)
	{
		UInventorySlotUI* SlotW = CreateWidget<UInventorySlotUI>(GetOwningPlayer(), SlotWidgetClass);
		SlotW->SlotIndex = Index;
		int32 Row = Index / NumColumns;
		int32 Col = Index % NumColumns;
		SlotGrid->AddChildToUniformGrid(SlotW, Row, Col);
		SlotWidgets.Add(SlotW);
	}

	// Bind update
	InventoryComp->OnInventoryUpdated.AddDynamic(this, &UInventoryUI::HandleInventoryUpdated);
	// Initial fill
	HandleInventoryUpdated();
}

void UInventoryUI::HandleInventoryUpdated()
{
	if (!InventoryComp)
		return;

	const TArray<FInventorySlot>& Slots = InventoryComp->GetSlots();
	int32 Capacity = SlotWidgets.Num();

	for (int32 Index = 0; Index < Capacity; ++Index)
	{
		UInventorySlotUI* SlotW = SlotWidgets[Index];
		if (SlotW)
		{
			if (Index < Slots.Num() && Slots[Index].Count > 0)
			{
				FItemData Def = InventoryComp->GetItemDefinition(Slots[Index].ItemID);
				SlotW->SetSlotData(Slots[Index], Def);
			}
			else
			{
				SlotW->SetEmptySlotData();
			}
		}
	}
}

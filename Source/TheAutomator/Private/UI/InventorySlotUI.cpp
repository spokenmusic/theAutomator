// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotUI.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/ItemData.h"

void UInventorySlotUI::SetSlotData(const FInventorySlot& SlotInfo, const FItemData& ItemDef)
{
	AmountBorder->SetVisibility(ESlateVisibility::HitTestInvisible);
	
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(ItemDef.Icon);
	}
	if (CountText)
	{
		CountText->SetText(FText::AsNumber(SlotInfo.Count));
	}
	// Show or hide the widget based on content
	if (SlotInfo.Count <= 0)
	{
		AmountBorder->SetVisibility(ESlateVisibility::Collapsed);
		IconImage->SetBrushFromTexture(EmptyIcon);
	}
}

void UInventorySlotUI::SetEmptySlotData()
{
	if (IconImage)
	{
		IconImage->SetBrushFromTexture(EmptyIcon);
	}
	if (AmountBorder)
	{
		AmountBorder->SetVisibility(ESlateVisibility::Collapsed);
	}
}

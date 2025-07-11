// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotUI.generated.h"

struct FItemData;
struct FInventorySlot;
/**
 * 
 */
UCLASS()
class THEAUTOMATOR_API UInventorySlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Initialize slot with data */
	UFUNCTION(BlueprintCallable, Category="Inventory Slot")
	void SetSlotData(const FInventorySlot& SlotInfo, const FItemData& ItemDef);

	UFUNCTION(BlueprintCallable, Category="Inventory Slot")
	void SetEmptySlotData();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Inventory")
	int32 SlotIndex;
protected:
	/** Icon image widget binding */
	UPROPERTY(meta = (BindWidget))
	class UImage* IconImage;

	/** Count text widget binding */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountText;

	UPROPERTY(meta = (BindWidget))
	class UBorder* AmountBorder;

	UPROPERTY(EditAnywhere,  Category= "Slots")
	class UTexture2D* EmptyIcon;
};

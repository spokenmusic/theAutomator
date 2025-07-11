// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class UInventorySlotUI;
class UInventoryComponent;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class THEAUTOMATOR_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Set up the UI with the inventory component */
	UFUNCTION(BlueprintCallable, Category="Inventory UI")
	void Initialize(UInventoryComponent* InvComp);

protected:
	virtual void NativeConstruct() override;

	/** Handler for inventory updates */
	UFUNCTION()
	void HandleInventoryUpdated();

	/** Grid panel to host slots */
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotGrid;

	/** Slot widget template class */
	UPROPERTY(EditAnywhere, Category="Inventory UI")
	TSubclassOf<UInventorySlotUI> SlotWidgetClass;

	/** Number of columns in the grid */
	UPROPERTY(EditAnywhere, Category="Inventory UI", meta=(ClampMin=1))
	int32 NumColumns = 5;

private:
	/** Pool of created slot widgets */
	UPROPERTY()
	TArray<UInventorySlotUI*> SlotWidgets;

	/** Reference to the inventory component */
	UPROPERTY()
	UInventoryComponent* InventoryComp;
};
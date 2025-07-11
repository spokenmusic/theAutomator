// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "ItemDataSubsystem.generated.h"

struct FItemData;
/**
 * 
 */
UCLASS()
class THEAUTOMATOR_API UItemDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Static accessor: get subsystem from any context object */
	UFUNCTION(BlueprintCallable, Category="ItemData", meta=(WorldContext="WorldContextObject"))
	static UItemDataSubsystem* GetItemDataSubsystem(UObject* WorldContextObject)
	{
		if (!WorldContextObject) return nullptr;
		UWorld* World = WorldContextObject->GetWorld();
		if (!World) return nullptr;
		UGameInstance* GI = World->GetGameInstance();
		return GI ? GI->GetSubsystem<UItemDataSubsystem>() : nullptr;
	}

	/** Retrieves the item definition by ItemID */
	UFUNCTION(BlueprintCallable, Category="ItemData")
	FItemData GetItemDefinition(FName ItemID) const;

	/** Check if item exists */
	UFUNCTION(BlueprintPure, Category="ItemData")
	bool IsValidItem(FName ItemID) const;

protected:
	/** DataTable containing all item definitions */
	UPROPERTY(EditDefaultsOnly, Category="ItemData")
	UDataTable* ItemDataTable;
};

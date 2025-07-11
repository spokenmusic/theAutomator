// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataSubsystem.h"
#include "Engine/DataTable.h"
#include "ItemData.h"
#include "Engine/World.h"

void UItemDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	static const FString Path = TEXT("/Game/DesignData/DT_ItemData.DT_ItemData");
	UDataTable* LoadedTable = Cast<UDataTable>(StaticLoadObject(
		UDataTable::StaticClass(),   // ← note capital ‘T’
		nullptr,
		*Path
	));

	if (!LoadedTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load ItemDataTable at %s"), *Path);
	}

	ItemDataTable = LoadedTable;
}

FItemData UItemDataSubsystem::GetItemDefinition(FName ItemID) const
{
	if (const UDataTable* DT = ItemDataTable)
	{
		for (auto& Pair : DT->GetRowMap())
		{
			const FItemData* Row = reinterpret_cast<const FItemData*>(Pair.Value);
			if (Row && Row->ItemID == ItemID)
			{
				return *Row;
			}
		}
	}
	// return an empty/default struct if missing
	return FItemData{};
}

bool UItemDataSubsystem::IsValidItem(FName ItemID) const
{
	FItemData Def = GetItemDefinition(ItemID);
	// We assume a missing/default struct has ItemID == NAME_None
	return Def.ItemID != NAME_None;
}


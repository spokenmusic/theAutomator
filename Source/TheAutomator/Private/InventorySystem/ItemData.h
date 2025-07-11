#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Tools UMETA(DisplayName = "Tools"),
	Raw UMETA(DisplayName = "Raw"),
	Built UMETA(DisplayName = "Built")
};

USTRUCT(BlueprintType)
struct THEAUTOMATOR_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Item")
	FName ItemID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Item")
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Item")
	EItemCategory ItemCategory;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Item")
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Item")
	int32 MaxStackSize = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Mesh")
	UStaticMesh* ItemMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Item")
	float ItemMeshScale = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Sound")
	USoundCue* PickupSound;
};
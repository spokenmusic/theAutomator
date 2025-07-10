#pragma once

USTRUCT(Blueprintable)
struct FItemData
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName ItemID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* Texture;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 MaxStackSize;
};

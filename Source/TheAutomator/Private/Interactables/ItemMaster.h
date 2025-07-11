// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableMaster.h"
#include "ItemMaster.generated.h"

UCLASS()
class THEAUTOMATOR_API AItemMaster : public AInteractableMaster
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemMaster();
	virtual void BeginPlay() override;
	virtual void Interaction(ACharacter* Character, UInventoryComponent* InventoryComponent = nullptr) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemQuantity;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Interactables)
	float ItemMeshScale;

private:
	FText ItemName;
};

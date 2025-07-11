// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableMaster.h"
#include "FactoryMachineMaster.generated.h"

UCLASS()
class THEAUTOMATOR_API AFactoryMachineMaster : public AInteractableMaster
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFactoryMachineMaster();

	UFUNCTION(BlueprintCallable, Category = "Factory")
	bool ReceiveItem(FName ItemID, int32 Quantity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Factory")
	UInventoryComponent* InputInventory;

	UPROPERTY(EditAnywhere, Category = "Factory")
	UDataAsset* RecipeAsset;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableMaster.generated.h"

class UInventoryComponent;

UCLASS()
class THEAUTOMATOR_API AInteractableMaster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableMaster();

	virtual bool CanInteract(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	virtual void Interaction(ACharacter* Character, UInventoryComponent* InventoryComponent = nullptr);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Sound")
	USoundCue* InteractSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interactables)
	class UStaticMeshComponent* ItemMeshComponent;
};

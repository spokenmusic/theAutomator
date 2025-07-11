// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerStatsSubsystem.generated.h"

/**
 * A global manager for player statistics (counters, metrics, achievements).
 * Accessible anywhere via GetPlayerStatsSubsystem.
 */
UCLASS()
class THEAUTOMATOR_API UPlayerStatsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Increment a named stat by a given amount (default +1) */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void IncrementStat(FName StatName, int32 Amount = 1);

	/** Set a stat to a specific value */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void SetStat(FName StatName, int32 Value);

	/** Get the current value of a stat (0 if not present) */
	UFUNCTION(BlueprintPure, Category="Stats")
	int32 GetStat(FName StatName) const;

	/** Reset a stat to zero (removes it) */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void ResetStat(FName StatName);

	/** Clear all stats */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void ResetAllStats();

	/** Static accessor for Blueprints and C++ */
	UFUNCTION(BlueprintPure, Category="Stats", meta=(WorldContext="WorldContextObject"))
	static UPlayerStatsSubsystem* GetPlayerStatsSubsystem(const UObject* WorldContextObject)
	{
		if (!WorldContextObject) return nullptr;
		UWorld* World = WorldContextObject->GetWorld();
		return World && World->GetGameInstance()
			? World->GetGameInstance()->GetSubsystem<UPlayerStatsSubsystem>()
			: nullptr;
	}

protected:
	// Internal map of stat names to values
	UPROPERTY()
	TMap<FName, int32> Stats;
};

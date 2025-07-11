// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsSubsystem.h"

void UPlayerStatsSubsystem::IncrementStat(FName StatName, int32 Amount)
{
	int32& Value = Stats.FindOrAdd(StatName);
	Value += Amount;
}

void UPlayerStatsSubsystem::SetStat(FName StatName, int32 Value)
{
	Stats.FindOrAdd(StatName) = Value;
}

int32 UPlayerStatsSubsystem::GetStat(FName StatName) const
{
	if (const int32* Found = Stats.Find(StatName))
	{
		return *Found;
	}
	return 0;
}

void UPlayerStatsSubsystem::ResetStat(FName StatName)
{
	Stats.Remove(StatName);
}

void UPlayerStatsSubsystem::ResetAllStats()
{
	Stats.Empty();
}

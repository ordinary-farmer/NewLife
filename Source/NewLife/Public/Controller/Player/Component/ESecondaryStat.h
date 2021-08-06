// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESecondaryStat : uint8
{
	DefensePower,
	MinDamage,
	MaxDamage,
	MaxHealthPoint,
	HealthPointRecoveryRate,
	MaxManaPoint,
	ManaPointRecoveryRate,
	CriticalHitProbability,
	MaxCount
};
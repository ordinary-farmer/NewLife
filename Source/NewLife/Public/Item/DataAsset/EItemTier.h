﻿// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemTier : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary,
	MaxCount
};

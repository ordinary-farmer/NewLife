// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerPermanentBuff : uint8
{
	Level,
    AvailableStatPoint,
    Strength,
    Dexterity,
    Vitality,
    Intelligence,
    MaxCount
};

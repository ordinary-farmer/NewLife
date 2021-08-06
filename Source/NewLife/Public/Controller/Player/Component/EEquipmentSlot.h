// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	HeadArmor,
    TorsoArmor,
    ShoulderArmor,
    LegArmor,
    ArmArmor,
    FirstRing,
    SecondRing,
    Necklace,
    RightHand,
    LeftHand,
    MaxCount
};
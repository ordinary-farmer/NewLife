// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemChangeEvent : uint8
{
	Insert,
    Release,
    Amount
};
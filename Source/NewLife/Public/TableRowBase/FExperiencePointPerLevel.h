// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FExperiencePointPerLevel.generated.h"

USTRUCT(BlueprintType)
struct FExperiencePointPerLevel : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxExperiencePoint;
};

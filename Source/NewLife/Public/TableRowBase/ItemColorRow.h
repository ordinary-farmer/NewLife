// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemColorRow.generated.h"

USTRUCT(BlueprintType)
struct FItemColorRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Color;
};

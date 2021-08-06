// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemInfoRow.generated.h"


USTRUCT(BlueprintType)
struct FItemInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId ItemID;	
};

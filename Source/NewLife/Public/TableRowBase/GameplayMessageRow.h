// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayMessageRow.generated.h"

USTRUCT(BlueprintType)
struct FGameplayMessageRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message;
};
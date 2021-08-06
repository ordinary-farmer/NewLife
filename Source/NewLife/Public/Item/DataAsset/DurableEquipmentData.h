// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/EquipmentData.h"
#include "DurableEquipmentData.generated.h"

/**
 * 
 */
UCLASS(HideDropdown)
class NEWLIFE_API UDurableEquipmentData : public UEquipmentData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin="1"))
	float MaxDurability;

public:
	FORCEINLINE float GetMaxDurability() const { return MaxDurability; }
};

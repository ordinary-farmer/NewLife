// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/EquipmentData.h"
#include "EAccessory.h"
#include "AccessoryData.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UAccessoryData : public UEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EAccessory AccessoryType;

public:
	UAccessoryData();

	virtual FGameplayTag GetItemTag() override;
	FORCEINLINE EAccessory GetAccessoryType() const { return AccessoryType; }
};

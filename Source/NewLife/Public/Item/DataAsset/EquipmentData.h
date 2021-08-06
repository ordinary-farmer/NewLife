// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/ItemData.h"
#include "Controller/Player/Component/EPrimaryStat.h"
#include "EquipmentData.generated.h"

UCLASS(HideDropdown)
class NEWLIFE_API UEquipmentData : public UItemData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EPrimaryStat, int32> EquipmentEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin="1"))
	int32 RequiredLevel;

public:
	UEquipmentData();
	
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:
	FORCEINLINE const TMap<EPrimaryStat, int32>& GetEquipmentEffects() const { return EquipmentEffects; }
	FORCEINLINE int32 GetRequiredLevel() const { return RequiredLevel; }
};

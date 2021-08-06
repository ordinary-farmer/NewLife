// Made By Park Joo Hyeong. This is my first Portfollio.

#include "Item/DataAsset/EquipmentData.h"

UEquipmentData::UEquipmentData()
	: RequiredLevel(1)
{
	bIsCountable = false;
	MaxAmount = 1;
	bHasAbility = false;
}

void UEquipmentData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(PropertyChangedEvent.GetPropertyName() == FName("EquipmentEffects"))
	{
		if (EquipmentEffects.Num() < 1)
		{
			ItemTier = EItemTier::Common;
		}
		else if (EquipmentEffects.Num() < 2)
		{
			ItemTier = EItemTier::Uncommon;
		}
		else if (EquipmentEffects.Num() < 3)
		{
			ItemTier = EItemTier::Rare;
		}
		else if (EquipmentEffects.Num() < 4)
		{
			ItemTier = EItemTier::Epic;
		}
		else
		{
			ItemTier = EItemTier::Legendary;
		}
	}
}

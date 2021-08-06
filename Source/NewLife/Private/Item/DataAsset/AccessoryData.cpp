// Made By Park Joo Hyeong. This is my first Portfollio.

#include "Item/DataAsset/AccessoryData.h"
#include "Singleton/ItemManagerSubsystem.h"

UAccessoryData::UAccessoryData()
{
	PrimaryAssetType = TEXT("Accessory");
	bHasAbility = true;
}

FGameplayTag UAccessoryData::GetItemTag()
{
	return ITEM_TAG_ACCESSORY;
}

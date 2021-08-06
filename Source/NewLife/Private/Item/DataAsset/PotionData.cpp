// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/DataAsset/PotionData.h"
#include "Singleton/ItemManagerSubsystem.h"

UPotionData::UPotionData()
{
	PrimaryAssetType = TEXT("Potion");
	bIsCountable = true;
}

FGameplayTag UPotionData::GetItemTag()
{
	return ITEM_TAG_POTION;
}

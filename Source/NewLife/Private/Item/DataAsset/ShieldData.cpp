// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/DataAsset/ShieldData.h"
#include "Singleton/ItemManagerSubsystem.h"

UShieldData::UShieldData()
{
	PrimaryAssetType = TEXT("Shield");
}

FGameplayTag UShieldData::GetItemTag()
{
	return ITEM_TAG_SHIELD;
}

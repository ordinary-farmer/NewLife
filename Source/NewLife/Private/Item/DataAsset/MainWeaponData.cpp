// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/DataAsset/MainWeaponData.h"
#include "Singleton/ItemManagerSubsystem.h"

UMainWeaponData::UMainWeaponData()
{
	PrimaryAssetType = TEXT("MainWeapon");
}

FGameplayTag UMainWeaponData::GetItemTag()
{
	return ITEM_TAG_MAIN_WEAPON;
}

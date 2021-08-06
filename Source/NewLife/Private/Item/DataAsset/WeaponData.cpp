// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/DataAsset/WeaponData.h"

UWeaponData::UWeaponData()
{
}

void UWeaponData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(MaxDamage < MinDamage)
	{
		MaxDamage = MinDamage;
	}
}

UStaticMesh* UWeaponData::GetLoadedBody() const
{
	if(BodyToLoad.Get() == nullptr)
	{
		return BodyToLoad.LoadSynchronous();
	}

	return BodyToLoad.Get();
}

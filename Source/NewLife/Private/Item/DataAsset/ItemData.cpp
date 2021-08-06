// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/DataAsset/ItemData.h"
#include "Ability/NLAbility.h"
#include "Singleton/ItemManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"

UItemData::UItemData()
	: PrimaryAssetType(TEXT("Item"))
	  , bHasAbility(true)
{
}

bool UItemData::CanEditChange(const FProperty* InProperty) const
{
	const bool ParentValue = Super::CanEditChange(InProperty);

	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UItemData, MaxAmount))
	{
		return ParentValue && bIsCountable;
	}
	
	if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UItemData, AbilityClass))
	{
		return ParentValue && bHasAbility;
	}
	
	return ParentValue;
}

FPrimaryAssetId UItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(PrimaryAssetType, GetFName());
}

UNLAbility* UItemData::GetAbility()
{
	if(Ability == nullptr && bHasAbility && AbilityClass)
	{
		Ability = NewObject<UNLAbility>(this, AbilityClass);
	}

	return Ability;
}
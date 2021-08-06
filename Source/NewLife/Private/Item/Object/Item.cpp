// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/Object/Item.h"
#include "Ability/NLAbility.h"
#include "Engine/AssetManager.h"
#include "Item/DataAsset/ItemData.h"
#include "Item/DataAsset/DurableEquipmentData.h"
#include "Singleton/ItemManagerSubsystem.h"

UItem::UItem()
	: ItemData(nullptr)
	  , Amount(0)
	  , bHasDurability(false)
	  , Durability(0.f)
{
}

void UItem::InitializeItem(UItemData* NewData)
{
	check(NewData != nullptr);

	ItemData = NewData;

	Amount = ItemData->GetMaxAmount();

	const FGameplayTag ItemTag = ItemData->GetItemTag();

	if(ItemTag.MatchesTag(ITEM_TAG_DURABLE_EQUIPMENT))
	{
		UDurableEquipmentData* DurableEquipmentData = Cast<UDurableEquipmentData>(ItemData);
		bHasDurability = true;
		Durability = DurableEquipmentData->GetMaxDurability();
	}
}

void UItem::Use()
{
	check(ItemData);

	UNLAbility* ItemAbility = ItemData->GetAbility();

	if (ItemAbility)
	{
		ItemAbility->Execute();
	}
}

int32 UItem::IncreaseAmountAndGetRemainder(int32 AmountToAdd)
{
	int32 Result = 0;

	Amount += AmountToAdd;

	if (Amount > ItemData->GetMaxAmount())
	{
		Result = Amount - ItemData->GetMaxAmount();
		Amount = ItemData->GetMaxAmount();
	}

	return Result;
}

void UItem::DecreaseAmount(int32 AmountToSub)
{
	Amount -= AmountToSub;
	Amount = Amount < 0 ? 0 : Amount;
}

void UItem::DecreaseDurability(float ValueToSub)
{
	Durability -= ValueToSub;

	Durability = Durability < 0.f ? 0.f : Durability;
}

void UItem::RecoverDurability()
{
	UDurableEquipmentData* DurableEquipmentData = Cast<UDurableEquipmentData>(ItemData);
	check(DurableEquipmentData);
	
	Durability = DurableEquipmentData->GetMaxDurability();
}

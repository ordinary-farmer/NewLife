// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Controller/Player/Component/InventoryComponent.h"
#include "Item/DataAsset/ItemData.h"
#include "Item/Object/Item.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UInventoryComponent::GetRowNum()
{
	return RowNum;
}

int32 UInventoryComponent::GetColumnNum()
{
	return ColumnNum;
}

UItem* UInventoryComponent::ReleaseItem(int32 Index)
{
	UItem* Result = Items[Index];
	Items[Index] = nullptr;

	if (OnItemChangedDelegate.IsBound())
	{
		OnItemChangedDelegate.Broadcast(Index, EItemChangeEvent::Release);
	}

	return Result;
}

UItem* UInventoryComponent::GetItem(int32 Index)
{
	return Items[Index];
}

void UInventoryComponent::InsertItem(int32 Index, UItem* Item)
{
	check(Items[Index] == nullptr);

	Items[Index] = Item;

	if (OnItemChangedDelegate.IsBound())
	{
		OnItemChangedDelegate.Broadcast(Index, EItemChangeEvent::Insert);
	}
}

void UInventoryComponent::PopulateTheSameItem(UItem* Item)
{
	FPrimaryAssetId ItemAssetId = Item->GetItemData()->GetPrimaryAssetId();

	int32 Amount = Item->GetAmount();

	for(int32 i = 0; i < Items.Num(); ++i)
	{
		if(Items[i] && ItemAssetId == Items[i]->GetItemData()->GetPrimaryAssetId())
		{
			const int32 TmpAmount = Items[i]->IncreaseAmountAndGetRemainder(Amount);

			if(TmpAmount != Amount)
			{
				if(OnItemChangedDelegate.IsBound())
				{
					OnItemChangedDelegate.Broadcast(i, EItemChangeEvent::Amount);
				}
			}

			Amount = TmpAmount;
			
			if(Amount == 0)
			{
				break;
			}			
		}
	}

	Item->DecreaseAmount(Item->GetAmount() - Amount);
}

void UInventoryComponent::InsertItemAtEmptyRoom(UItem* Item)
{
	EmptyRoomCount--;
	
	const int32 EmptyRoomIndex = GetEmptyRoomIndex();
	check(EmptyRoomIndex != NO_EMPTY_ROOM);

	Items[EmptyRoomIndex] = Item;

	if (OnItemChangedDelegate.IsBound())
	{
		OnItemChangedDelegate.Broadcast(EmptyRoomIndex, EItemChangeEvent::Insert);
	}
}

int32 UInventoryComponent::GetEmptyRoomCount() const
{
	return EmptyRoomCount;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.Init(nullptr, RowNum * ColumnNum);
	EmptyRoomCount = RowNum * ColumnNum;
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnItemChangedDelegate.Clear();
}

int32 UInventoryComponent::GetEmptyRoomIndex()
{
	int32 i = 0;

	for (auto* EachSlot : Items)
	{
		if (EachSlot == nullptr)
		{
			return i;
		}

		i++;
	}

	return NO_EMPTY_ROOM;
}

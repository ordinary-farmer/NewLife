// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Singleton/ItemManagerSubsystem.h"
#include "Engine/DataTable.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/ItemData.h"
#include "Item/DataAsset/EItemTier.h"
#include "TableRowBase/ItemColorRow.h"
#include "GameplayTagsManager.h"
#include "Engine/AssetManager.h"

#include "Item/DataAsset/DurableEquipmentData.h"

void UItemManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ItemColorTable = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/_NewLife/DataTable/ItemColorTable.ItemColorTable'"));
}

void UItemManagerSubsystem::Deinitialize()
{
}

FLinearColor UItemManagerSubsystem::GetItemColor(UItemData* Data)
{
	check(ItemColorTable);

	const FGameplayTag ItemTag = Data->GetItemTag();
	
	FItemColorRow* ItemColorRow = nullptr;	

	if(ItemTag.MatchesTag(ITEM_TAG_EQUIPMENT))
	{
		const EItemTier Tier = Cast<UEquipmentData>(Data)->GetItemTier();
		
		switch (Tier)
		{
		case EItemTier::Common:
			ItemColorRow = ItemColorTable->FindRow<FItemColorRow>("Common", TEXT(""));
			break;
		case EItemTier::Uncommon:
			ItemColorRow = ItemColorTable->FindRow<FItemColorRow>("Uncommon", TEXT(""));
			break;
		case EItemTier::Rare:
			ItemColorRow = ItemColorTable->FindRow<FItemColorRow>("Rare", TEXT(""));
			break;
		case EItemTier::Epic:
			ItemColorRow = ItemColorTable->FindRow<FItemColorRow>("Epic", TEXT(""));
			break;
		case EItemTier::Legendary:
			ItemColorRow = ItemColorTable->FindRow<FItemColorRow>("Legendary", TEXT(""));
			break;
		default:
			checkNoEntry();
		}
	}
	else if(ItemTag.MatchesTag(ITEM_TAG_POTION))
	{
		ItemColorRow = ItemColorTable->FindRow<FItemColorRow>("Common", TEXT(""));
	}

	checkf(ItemColorRow, TEXT("Failed to find item color."));
	
	return ItemColorRow->Color;
}

void UItemManagerSubsystem::CreateItemWithAsyncLoad(FPrimaryAssetId ItemAssetId, UItem** ItemAddressToInsert, UObject* Outer)
{
	if(*ItemAddressToInsert != nullptr)
	{
		return;
	}
	
	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	check(AssetManager);

	TArray<FName> Bundles;

	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(
        this, &UItemManagerSubsystem::OnPrimaryItemAssetLoadCompleted, ItemAssetId, ItemAddressToInsert, Outer);

	AssetManager->LoadPrimaryAsset(ItemAssetId, Bundles, Delegate);
}

void UItemManagerSubsystem::ForceLoadAndCreateItem(FPrimaryAssetId ItemAssetId, UItem** ItemAddressToInsert, UObject* Outer)
{
	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	check(AssetManager);

	FSoftObjectPath AssetPath = AssetManager->GetPrimaryAssetPath(ItemAssetId);
	
	UItemData* LoadedItemData = Cast<UItemData>(AssetPath.TryLoad());

	checkf(LoadedItemData, TEXT("Sync Load is failed."));

	*ItemAddressToInsert = CreateItem(LoadedItemData, Outer);
}

void UItemManagerSubsystem::AsyncLoadSecondaryAssets(UItemData* ItemData)
{
	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	check(AssetManager);

	TArray<FName> Bundles;
	Bundles.Add("SecondaryAsset");

	const FStreamableDelegate EmptyDelegate;

	AssetManager->LoadPrimaryAsset(ItemData->GetPrimaryAssetId(), Bundles, EmptyDelegate);
}

void UItemManagerSubsystem::OnPrimaryItemAssetLoadCompleted(FPrimaryAssetId ItemAssetId, UItem** ItemAddressToInsert, UObject* Outer)
{
	if(*ItemAddressToInsert == nullptr)
	{
		UAssetManager* AssetManager = UAssetManager::GetIfValid();
		check(AssetManager);

		UItemData* LoadedItemData = Cast<UItemData>(AssetManager->GetPrimaryAssetObject(ItemAssetId));
		check(LoadedItemData);

		*ItemAddressToInsert = CreateItem(LoadedItemData, Outer);
	}
	
	AsyncLoadSecondaryAssets((*ItemAddressToInsert)->GetItemData());
}

UItem* UItemManagerSubsystem::CreateItem(UItemData* Data, UObject* Outer)
{
	UItem* NewItem = NewObject<UItem>(Outer);
	
	NewItem->InitializeItem(Data);

	return NewItem;
}
// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWEquipmentInfo.h"
#include "Components/Image.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/ItemData.h"
#include "Singleton/ItemManagerSubsystem.h"

void UUWEquipmentInfo::UpdateInfo(UItem* LinkedItem)
{
	check(LinkedItem);
	UItemData* ItemData = LinkedItem->GetItemData();
	
	UTexture2D* ItemIconTexture = ItemData->GetItemIcon();
	ItemIcon->SetBrushFromTexture(ItemIconTexture);

	UGameInstance* GameInstance = GetGameInstance();
	check(GameInstance);

	UItemManagerSubsystem* ItemManager = GameInstance->GetSubsystem<UItemManagerSubsystem>();
	check(ItemManager);
	
	BorderColor = ItemManager->GetItemColor(ItemData);
}

// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWItemInfo.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/ItemData.h"
#include "Singleton/ItemManagerSubsystem.h"
#include "Singleton/NLGameInstance.h"

void UUWItemInfo::UpdateInfo(UItem* LinkedItem)
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

	if(ItemData->IsCountable())
	{
		AmountTextVisibility = ESlateVisibility::Visible;
		UpdateAmountText(LinkedItem);
	}
	else
	{
		AmountTextVisibility = ESlateVisibility::Hidden;		
	}
}

void UUWItemInfo::UpdateAmountText(UItem* LinkedItem)
{
	check(LinkedItem);
	AmountText->SetText(FText::AsNumber(LinkedItem->GetAmount()));
}

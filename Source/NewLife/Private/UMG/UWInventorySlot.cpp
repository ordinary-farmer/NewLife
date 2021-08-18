// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWInventorySlot.h"

#include "GameplayTagContainer.h"

#include "Item/Object/Item.h"
#include "UMG/UWItemInfo.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroEquipmentComponent.h"

#include "UMG/UWGameHUD.h"
#include "UMG/UWItemHoverInfo.h"
#include "Controller/Player/Component/MouseInfoComponent.h"
#include "Interface/InventoryInterface.h"


#include "Item/DataAsset/AccessoryData.h"
#include "Item/DataAsset/ArmorData.h"
#include "Item/DataAsset/ItemData.h"

#include "UMG/UWInventory.h"

IInventoryInterface* UUWInventorySlot::InventoryInterface = nullptr;

UUWInventorySlot::UUWInventorySlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , ItemInfoVisibility(ESlateVisibility::Hidden)
	  , bSetLinkedItem(false)
{
}

void UUWInventorySlot::Activate(UItem* LinkedItem)
{
	bSetLinkedItem = true;
	ItemInfoVisibility = ESlateVisibility::Visible;
	ItemInfo->UpdateInfo(LinkedItem);
}

void UUWInventorySlot::Deactivate()
{
	bSetLinkedItem = false;
	ItemInfoVisibility = ESlateVisibility::Hidden;
}

void UUWInventorySlot::ChangeAmountText(UItem* LinkedItem)
{
	ItemInfo->UpdateAmountText(LinkedItem);
}

void UUWInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bSetLinkedItem == false)
	{
		return;
	}

	UItem* LinkedItem = InventoryInterface->GetItem(Index);
	check(LinkedItem);

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->GetItemHoverInfoWidget();
	ItemHoverInfo->Update(LinkedItem);
	ItemHoverInfo->SetItemHoverInfoOnItem(true);
}

void UUWInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (bSetLinkedItem == false)
	{
		return;
	}

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->GetItemHoverInfoWidget();
	ItemHoverInfo->SetItemHoverInfoOnItem(false);
}

void UUWInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton->OnClicked.AddDynamic(this, &UUWInventorySlot::OnSlotButtonClicked);
}

FReply UUWInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")) && InventoryInterface->GetItem(Index) != nullptr)
	{
		UItem* LinkedItem = InventoryInterface->GetItem(Index);
		UItemData* ItemData = LinkedItem->GetItemData();

		FGameplayTag ItemTag = ItemData->GetItemTag();

		ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
		check(PlayerController);
		
		if (ItemTag.MatchesTag(ITEM_TAG_EQUIPMENT))
		{
			UHeroEquipmentComponent* HeroEquipmentComp = PlayerController->GetHeroEquipmentComp();
			check(HeroEquipmentComp);

			EEquipmentSlot EquipmentSlotToChange = EEquipmentSlot::MaxCount;
			
			if (ItemTag.MatchesTag(ITEM_TAG_ARMOR))
			{
				UArmorData* ArmorData = Cast<UArmorData>(ItemData);
				check(ArmorData);

				switch (ArmorData->GetArmorType())
				{
				case EArmor::Head:
					EquipmentSlotToChange = EEquipmentSlot::HeadArmor;
					break;
				case EArmor::Shoulder:
					EquipmentSlotToChange = EEquipmentSlot::ShoulderArmor;
					break;
				case EArmor::Torso:
					EquipmentSlotToChange = EEquipmentSlot::TorsoArmor;
					break;
				case EArmor::Leg:
					EquipmentSlotToChange = EEquipmentSlot::LegArmor;
					break;
				case EArmor::Arm:
					EquipmentSlotToChange = EEquipmentSlot::ArmArmor;
					break;
				default:
					checkNoEntry();
				}
			}
			else if (ItemTag.MatchesTag(ITEM_TAG_ACCESSORY))
			{
				UAccessoryData* AccessoryData = Cast<UAccessoryData>(ItemData);
				check(AccessoryData);

				switch (AccessoryData->GetAccessoryType())
				{
				case EAccessory::Necklace:
					EquipmentSlotToChange = EEquipmentSlot::Necklace;
					break;
				case EAccessory::Ring:
					if(HeroEquipmentComp->GetEquipment(EEquipmentSlot::FirstRing) && HeroEquipmentComp->GetEquipment(EEquipmentSlot::SecondRing) == nullptr)
					{
						EquipmentSlotToChange = EEquipmentSlot::SecondRing;
					}
					else
					{
						EquipmentSlotToChange = EEquipmentSlot::FirstRing;
					}
					break;
				default:
					checkNoEntry();
				}
			}
			else if (ItemTag.MatchesTag(ITEM_TAG_MAIN_WEAPON))
			{
				EquipmentSlotToChange = EEquipmentSlot::RightHand;
			}
			else if (ItemTag.MatchesTag(ITEM_TAG_SHIELD))
			{
				EquipmentSlotToChange = EEquipmentSlot::LeftHand;
			}
			else
			{
				check(false);
			}

			UItem* TmpItem = InventoryInterface->ReleaseItem(Index);

			if(HeroEquipmentComp->GetEquipment(EquipmentSlotToChange) != nullptr)
			{
				InventoryInterface->InsertItem(Index, HeroEquipmentComp->ReleaseItem(EquipmentSlotToChange));
			}
			
			HeroEquipmentComp->InsertItem(EquipmentSlotToChange, TmpItem);

			UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->GetItemHoverInfoWidget();

			if(InventoryInterface->GetItem(Index) == nullptr)
			{
				ItemHoverInfo->SetItemHoverInfoOnItem(false);
			}
			else
			{
				ItemHoverInfo->SetItemHoverInfoOnItem(true);
				ItemHoverInfo->Update(InventoryInterface->GetItem(Index));
			}
		}
		else
		{
			bool bIsUsed = LinkedItem->Use(PlayerController);

			if(bIsUsed)
			{
				ChangeAmountText(LinkedItem);
			
				if(LinkedItem->GetAmount() == 0)
				{
					Deactivate();
				}
			}			
		}
	}
	return FReply::Handled();
}

void UUWInventorySlot::OnSlotButtonClicked()
{
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UMouseInfoComponent* MouseInfo = PlayerController->GetMouseInfoComp();
	check(MouseInfo);

	// 버튼을 클릭했을 때 네가지의 경우의 수가 있음
	// 1. 슬롯에 링크된 아이템이 없고 마우스커서가 아이템을 들고 있지 않을 때
	if (!bSetLinkedItem && !MouseInfo->GetIsCarryingItem())
	{
		return;
	}

	// 2. 슬롯에 링크된 아이템이 없고 마우스 커서가 아이템을 들고 있을 때
	if (!bSetLinkedItem && MouseInfo->GetIsCarryingItem())
	{
		InventoryInterface->InsertItem(Index, MouseInfo->ReleaseCarryingItem());

		UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->
		                                                    GetItemHoverInfoWidget();
		ItemHoverInfo->Update(InventoryInterface->GetItem(Index));
		ItemHoverInfo->SetItemHoverInfoOnItem(true);
	}
		// 3. 슬롯에 링크된 아이템이 있고 마우스 커서가 아이템을 들고 있지 않을 때
	else if (bSetLinkedItem && !MouseInfo->GetIsCarryingItem())
	{
		MouseInfo->ReceiveCarryingItem(Index, InventoryInterface->ReleaseItem(Index));
	}
		// 4. 슬롯에 링크된 아이템이 있고 마우스 커서가 아이템을 들고 있을 때
	else if (bSetLinkedItem && MouseInfo->GetIsCarryingItem())
	{
		UItem* TmpItem = InventoryInterface->ReleaseItem(Index);
		InventoryInterface->InsertItem(Index, MouseInfo->ReleaseCarryingItem());
		MouseInfo->ReceiveCarryingItem(TmpItem);
	}

	// 호버인포가 HUD에 띄워져야 하는 상황 1. 마우스가 아이템을 들고 있지 않는다 2. 해당 슬롯에 아이템이 있다.
}

void UUWInventorySlot::SetInventoryInterface(IInventoryInterface* NewInventoryInterface)
{
	InventoryInterface = NewInventoryInterface;
}

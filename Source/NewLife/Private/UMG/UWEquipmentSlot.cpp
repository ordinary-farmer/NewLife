// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWEquipmentSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroEquipmentComponent.h"
#include "Controller/Player/Component/InventoryComponent.h"
#include "Controller/Player/Component/MouseInfoComponent.h"
#include "Item/DataAsset/AccessoryData.h"
#include "Item/DataAsset/ArmorData.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/ItemData.h"

#include "Singleton/GameplayMessageHandlerSubsystem.h"

#include "UMG/UWEquipmentInfo.h"
#include "UMG/UWItemHoverInfo.h"
#include "UMG/UWGameHUD.h"
#include "UMG/UWInventory.h"


void UUWEquipmentSlot::SetEmptySlotImage(UTexture2D* NewTexture)
{
	EmptySlotImage->SetBrushFromTexture(NewTexture);
}

void UUWEquipmentSlot::Update()
{
	UItem* LinkedItem = HeroEquipmentComp->GetEquipment(EquipmentSlotType);

	if(LinkedItem != nullptr)
	{
		SlotWidgetSwitcher->SetActiveWidgetIndex(WIDGET_SWITCHER_INDEX_FULL_SLOT);
		EquipmentInfo->UpdateInfo(LinkedItem);
	}
	else
	{
		SlotWidgetSwitcher->SetActiveWidgetIndex(WIDGET_SWITCHER_INDEX_EMPTY_SLOT);
	}
}

void UUWEquipmentSlot::NativePreConstruct()
{
	if(EmptySlotImageTexture)
	{
		EmptySlotImage->SetBrushFromTexture(EmptySlotImageTexture);
	}
}

void UUWEquipmentSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (SlotWidgetSwitcher->ActiveWidgetIndex == WIDGET_SWITCHER_INDEX_EMPTY_SLOT)
	{
		return;
	}

	UItem* LinkedItem = HeroEquipmentComp->GetEquipment(EquipmentSlotType);
	check(LinkedItem);

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->GetItemHoverInfoWidget();
	ItemHoverInfo->Update(LinkedItem);
	ItemHoverInfo->SetItemHoverInfoOnItem(true);
}

void UUWEquipmentSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (SlotWidgetSwitcher->ActiveWidgetIndex == WIDGET_SWITCHER_INDEX_EMPTY_SLOT)
	{
		return;
	}

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->GetItemHoverInfoWidget();
	ItemHoverInfo->SetItemHoverInfoOnItem(false);
}

void UUWEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton->OnClicked.AddDynamic(this, &UUWEquipmentSlot::OnSlotButtonClicked);

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UHeroEquipmentComponent* NewHeroEquipmentComp = PlayerController->GetHeroEquipmentComp();
	check(NewHeroEquipmentComp);

	HeroEquipmentComp = NewHeroEquipmentComp;
}

FReply UUWEquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{
		ANLPlayerController* PC = Cast<ANLPlayerController>(GetOwningPlayer());
		check(PC);

		UInventoryComponent* InventoryComp = PC->GetInventoryComp();

		if(InventoryComp->GetEmptyRoomCount() > 0)
		{
			const int32 IndexToInsert = InventoryComp->GetEmptyRoomIndex();

			InventoryComp->InsertItem(IndexToInsert, HeroEquipmentComp->ReleaseItem(EquipmentSlotType));

			UUWItemHoverInfo* ItemHoverInfo = PC->GetGameHUD()->GetInventoryWidget()->GetItemHoverInfoWidget();
			ItemHoverInfo->SetItemHoverInfoOnItem(false);
		}
		else
		{
			UGameInstance* GameInstance = GetGameInstance();
			UGameplayMessageHandlerSubsystem* GameplayMessageHandler = GameInstance->GetSubsystem<UGameplayMessageHandlerSubsystem>();

			GameplayMessageHandler->DisplayMessage(FString("BagFull"));
			
			UE_LOG(LogTemp, Warning, TEXT("Can't UnEquip!"));
		}
	}
	return FReply::Handled();
}

void UUWEquipmentSlot::OnSlotButtonClicked()
{
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UMouseInfoComponent* MouseInfo = PlayerController->GetMouseInfoComp();
	check(MouseInfo);

	if (MouseInfo->GetIsCarryingItem() && !IsPossibleToInsert(MouseInfo->GetCarryingItem()))
	{
		UGameInstance* GameInstance = GetGameInstance();
		UGameplayMessageHandlerSubsystem* GameplayMessageHandler = GameInstance->GetSubsystem<UGameplayMessageHandlerSubsystem>();

		GameplayMessageHandler->DisplayMessage(FString("CanNotEquip"));
		
		UE_LOG(LogTemp, Warning, TEXT("Can't Insert This Item!!!"));
		return;
	}

	// auto& Equipments = PlayerInfo->GetEquipments();
	// UItem** LinkedEquipmentAddress = Equipments.Find(EquipmentSlotType);

	if (SlotWidgetSwitcher->ActiveWidgetIndex == WIDGET_SWITCHER_INDEX_EMPTY_SLOT)
	{
		if (MouseInfo->GetIsCarryingItem())
		{
			// 슬롯이 비어있고 마우스가 아이템을 들고 있을 때
			HeroEquipmentComp->InsertItem(EquipmentSlotType, MouseInfo->ReleaseCarryingItem());
			//*LinkedEquipmentAddress = MouseInfo->ReleaseCarryingItem();

			UUWItemHoverInfo* ItemHoverInfo = PlayerController->GetGameHUD()->GetInventoryWidget()->
			                                                    GetItemHoverInfoWidget();
			ItemHoverInfo->Update(HeroEquipmentComp->GetEquipment(EquipmentSlotType));
			ItemHoverInfo->SetItemHoverInfoOnItem(true);
		}
	}
	else
	{
		if (MouseInfo->GetIsCarryingItem())
		{
			// 슬롯에 아이템이 있고 마우스가 아이템을 들고 있을 때
			UItem* TmpItem = HeroEquipmentComp->ReleaseItem(EquipmentSlotType);
			UItem* TmpItem2 = MouseInfo->ReleaseCarryingItem();
			HeroEquipmentComp->InsertItem(EquipmentSlotType, TmpItem2);
			MouseInfo->ReceiveCarryingItem(TmpItem);
		}
		else
		{
			// 슬롯에 아이템이 있고 마우스가 아이템을 들고 있지 않을 때
			MouseInfo->ReceiveCarryingItem(HeroEquipmentComp->ReleaseItem(EquipmentSlotType));
			SlotWidgetSwitcher->SetActiveWidgetIndex(WIDGET_SWITCHER_INDEX_EMPTY_SLOT);
		}
	}
}

bool UUWEquipmentSlot::IsPossibleToInsert(UItem* Item)
{
	const FGameplayTag ItemTag = Item->GetItemData()->GetItemTag();
	bool Result = false;

	if (ItemTag.MatchesTag(ITEM_TAG_ARMOR))
	{
		UArmorData* ArmorData = Cast<UArmorData>(Item->GetItemData());
		check(ArmorData);

		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::HeadArmor:
			if (ArmorData->GetArmorType() == EArmor::Head)
			{
				Result = true;
			}
			break;
		case EEquipmentSlot::TorsoArmor:
			if (ArmorData->GetArmorType() == EArmor::Torso)
			{
				Result = true;
			}
			break;
		case EEquipmentSlot::ShoulderArmor:
			if (ArmorData->GetArmorType() == EArmor::Shoulder)
			{
				Result = true;
			}
			break;
		case EEquipmentSlot::LegArmor:
			if (ArmorData->GetArmorType() == EArmor::Leg)
			{
				Result = true;
			}
			break;
		case EEquipmentSlot::ArmArmor:
			if (ArmorData->GetArmorType() == EArmor::Arm)
			{
				Result = true;
			}
			break;
		default:
			break;
		}
	}
	else if (ItemTag.MatchesTag(ITEM_TAG_ACCESSORY))
	{
		UAccessoryData* AccessoryData = Cast<UAccessoryData>(Item->GetItemData());
		check(AccessoryData);

		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::FirstRing:
			// Intentional fall through
		case EEquipmentSlot::SecondRing:
			if (AccessoryData->GetAccessoryType() == EAccessory::Ring)
			{
				Result = true;
			}
			break;
		case EEquipmentSlot::Necklace:
			if (AccessoryData->GetAccessoryType() == EAccessory::Necklace)
			{
				Result = true;
			}
			break;
		default:
			break;
		}
	}
	else if (ItemTag.MatchesTag(ITEM_TAG_WEAPON))
	{
		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::RightHand:
			if (ItemTag.MatchesTag(ITEM_TAG_MAIN_WEAPON) && !ItemTag.MatchesTag(ITEM_TAG_SHIELD))
			{
				Result = true;
			}
			break;
		case EEquipmentSlot::LeftHand:
			if (ItemTag.MatchesTag(ITEM_TAG_MAIN_WEAPON) || ItemTag.MatchesTag(ITEM_TAG_SHIELD))
			{
				Result = true;
			}
			break;
		default:
			break;
		}
	}

	return Result;
}

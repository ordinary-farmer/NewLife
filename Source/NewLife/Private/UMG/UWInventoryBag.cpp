// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWInventoryBag.h"
#include "Components/UniformGridPanel.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/InventoryComponent.h"
#include "UMG/UWInventorySlot.h"

void UUWInventoryBag::NativeConstruct()
{
	Super::NativeConstruct();
	
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	PlayerController->GetInventoryComp()->SetInventoryBagWidget(this);
	PlayerController->GetInventoryComp()->OnItemChangedDelegate.AddDynamic(this, &UUWInventoryBag::OnItemChanged);

	InventoryInterface = PlayerController->GetInventoryComp();
	check(InventoryInterface);

	RowSlotCount = InventoryInterface->GetRowNum();
	ColumnSlotCount = InventoryInterface->GetColumnNum();

	const int32 MaxSlotsCount = RowSlotCount * ColumnSlotCount;

	for (int32 i = 0; i < MaxSlotsCount; ++i)
	{
		const int32 RowIndex = i / ColumnSlotCount;
		const int32 ColumnIndex = i % ColumnSlotCount;

		UUWInventorySlot* InventorySlotWidget = Cast<UUWInventorySlot>(CreateWidget(this, InventorySlotWidgetClass));
		InventorySlotWidget->SetIndex(i);
		InventorySlotWidgets.Emplace(InventorySlotWidget);

		SlotPanel->AddChildToUniformGrid(InventorySlotWidget, RowIndex, ColumnIndex);
	}

	UUWInventorySlot::SetInventoryInterface(Cast<IInventoryInterface>(PlayerController->GetInventoryComp()));
}

void UUWInventoryBag::OnItemChanged(int32 SlotIndex, EItemChangeEvent ItemChangeEvent)
{
	check(InventoryInterface);
	
	switch (ItemChangeEvent)
	{
	case EItemChangeEvent::Insert:
		{
			UItem* Item = InventoryInterface->GetItem(SlotIndex);
			InventorySlotWidgets[SlotIndex]->Activate(Item);
		}
		break;
	case EItemChangeEvent::Release:
		InventorySlotWidgets[SlotIndex]->Deactivate();
		break;
	case EItemChangeEvent::Amount:
		{
			UItem* Item = InventoryInterface->GetItem(SlotIndex);
			InventorySlotWidgets[SlotIndex]->ChangeAmountText(Item);
		}
		break;
	default:
		checkNoEntry();
	}
}

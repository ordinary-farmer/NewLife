// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Controller/Player/Component/MouseInfoComponent.h"
#include "Controller/Player/NLPlayerController.h"
#include "UMG/UWMouseCursor.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/ItemData.h"

// Sets default values for this component's properties
UMouseInfoComponent::UMouseInfoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UItem* UMouseInfoComponent::ReleaseCarryingItem()
{
	UItem* Result = CarryingItem;
	
	CarryingItem = nullptr;
	CarryingItemIndex = NO_CARRYING_ITEM;

	SwitchCursorToDefault();
	
	return Result;
}

void UMouseInfoComponent::FreeCarryingItem()
{
	if(CarryingItem == nullptr)
	{
		return;
	}
	
	CarryingItem->ConditionalBeginDestroy();
	
	CarryingItem = nullptr;
	CarryingItemIndex = NO_CARRYING_ITEM;

	SwitchCursorToDefault();
}

void UMouseInfoComponent::ReceiveCarryingItem(int32 Index, UItem* Item)
{
	CarryingItemIndex = Index;
	ReceiveCarryingItem(Item);
}

void UMouseInfoComponent::ReceiveCarryingItem(UItem* Item)
{
	CarryingItem = Item;

	SwitchCursorToItem(Item->GetItemData()->GetItemIcon());
}

void UMouseInfoComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	
	DefaultCursor = Cast<UUWMouseCursor>(CreateWidget(PlayerController, DefaultCursorClass));
	check(DefaultCursor);

	ItemCursor = Cast<UUWMouseCursor>(CreateWidget(PlayerController, ItemCursorClass));
	check(ItemCursor);

	SwitchCursorToDefault();	
}

void UMouseInfoComponent::SwitchCursorToDefault()
{
	check(DefaultCursor);
	
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	check(PlayerController);

	PlayerController->SetMouseCursorWidget(EMouseCursor::Default, DefaultCursor);
}

void UMouseInfoComponent::SwitchCursorToItem(UTexture2D* NewItemTexture)
{
	check(ItemCursor);

	ItemCursor->SetCursorImage(NewItemTexture);
	
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	check(PlayerController);

	PlayerController->SetMouseCursorWidget(EMouseCursor::Default, ItemCursor);
}


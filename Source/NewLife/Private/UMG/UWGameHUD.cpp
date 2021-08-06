// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWGameHUD.h"
#include "Components/CanvasPanelSlot.h"
#include "UMG/UWItemHoverInfo.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/MouseInfoComponent.h"
#include "UMG/UWInventory.h"
#include "UMG/UWCompassBar.h"
#include "Components/CanvasPanel.h"

UUWGameHUD::UUWGameHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
	, InventoryWidgetVisibility(ESlateVisibility::Hidden)
{
}

void UUWGameHUD::ToggleInventoryWidget()
{
	APlayerController* PlayerController = GetOwningPlayer();
	
	if(InventoryWidgetVisibility == ESlateVisibility::Hidden)
	{
		InventoryWidgetVisibility = ESlateVisibility::Visible;
		
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetWidgetToFocus(InventoryWidget->GetCachedWidget());

		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
	}
	else if(InventoryWidgetVisibility == ESlateVisibility::Visible)
	{
		InventoryWidgetVisibility = ESlateVisibility::Hidden;

		FInputModeGameOnly InputMode;

		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(false);
	}
}

void UUWGameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UUWItemHoverInfo* ItemHoverInfoWidget = InventoryWidget->GetItemHoverInfoWidget();

	if(ItemHoverInfoWidget->GetItemHoverInfoOnItem() && !PlayerController->GetMouseInfoComp()->GetIsCarryingItem())
	{
		UCanvasPanelSlot* InfoAsSlot = Cast<UCanvasPanelSlot>(ItemHoverInfoWidget->Slot);

		FVector2D NewItemHoverInfoLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		NewItemHoverInfoLocation.X += 20.f;
		NewItemHoverInfoLocation.Y += 20.f;
		
		InfoAsSlot->SetPosition(NewItemHoverInfoLocation);

		InventoryWidget->SetItemHoverInfoVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		InventoryWidget->SetItemHoverInfoVisibility(ESlateVisibility::Hidden);
	}
}

void UUWGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
	//
	// check(InventoryWidgetClass.Get());
	// InventoryWidget = CreateWidget<UUWInventory>(this, InventoryWidgetClass.Get());
	
	// Inventory = Cast<UUWInventory>(CreateWidget(this, UUWInventory::StaticClass()));
}

// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWInventory.h"
#include "Components/Border.h"
#include "UMG/UWInventorySlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/MouseInfoComponent.h"

#include "UMG/UWItemHoverInfo.h"

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackGroundBorder->OnMouseButtonDownEvent.BindDynamic(this, &UUWInventory::OnBackGroundBorderClicked);
}

FEventReply UUWInventory::OnBackGroundBorderClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	// if(MouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("BackGroundBorderClicked!"));	
	// }

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UMouseInfoComponent* MouseInfoComp = PlayerController->GetMouseInfoComp();
	check(MouseInfoComp);

	MouseInfoComp->FreeCarryingItem();

	ItemHoverInfoWidget->SetItemHoverInfoOnItem(false);

	return UWidgetBlueprintLibrary::Handled();
}

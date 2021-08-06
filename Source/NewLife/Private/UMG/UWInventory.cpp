// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWInventory.h"

#include "Components/Border.h"
#include "UMG/UWInventorySlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();
	
	BackGroundBorder->OnMouseButtonDownEvent.BindDynamic(this, &UUWInventory::OnBackGroundBorderClicked);
}

FEventReply UUWInventory::OnBackGroundBorderClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	if(MouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{
		UE_LOG(LogTemp, Warning, TEXT("BackGroundBorderClicked!"));	
	}
	return UWidgetBlueprintLibrary::Handled();	
}

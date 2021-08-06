// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWInteractiveObjectMark.h"
#include "Components/Image.h"

void UUWInteractiveObjectMark::SetMarkDot()
{
	Mark->SetBrushFromTexture(Dot);
}

void UUWInteractiveObjectMark::SetMarkCircleDot()
{
	Mark->SetBrushFromTexture(CircleDot);
}

void UUWInteractiveObjectMark::NativeConstruct()
{
	Super::NativeConstruct();
	
	Mark = Cast<UImage>(GetWidgetFromName("DSN_Mark"));
	Mark->SetBrushFromTexture(Dot);
}

// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWInteractHelper.h"

void UUWInteractHelper::SetInteractText(FText NewText)
{
	InteractText = NewText;
}

void UUWInteractHelper::NativePreConstruct()
{
	InteractText = FText::FromString("InteractText");
}

// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Pawn/Player/Components/InteractHelperWidgetComponent.h"

#include "UMG/UWInteractHelper.h"

UInteractHelperWidgetComponent::UInteractHelperWidgetComponent()
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawSize(FVector2D(48.f, 48.f));
	SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(
        TEXT("WidgetBlueprint'/Game/_NewLife/UI/WB_InteractHelper.WB_InteractHelper_C'"));
	if (WidgetAsset.Succeeded())
	{
		SetWidgetClass(WidgetAsset.Class);
	}
}

void UInteractHelperWidgetComponent::UpdateText(FText NewText)
{
	UUWInteractHelper* MyWidget = Cast<UUWInteractHelper>(GetWidget());
	check(MyWidget);

	MyWidget->SetInteractText(NewText);
}

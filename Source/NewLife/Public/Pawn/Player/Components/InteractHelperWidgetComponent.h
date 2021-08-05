// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractHelperWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UInteractHelperWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UInteractHelperWidgetComponent();

	void UpdateText(FText NewText);
};

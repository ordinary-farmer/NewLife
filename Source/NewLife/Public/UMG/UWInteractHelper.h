// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInteractHelper.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWInteractHelper : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText InteractText;

public:
	void SetInteractText(FText NewText);

protected:
	virtual void NativePreConstruct() override;
	
};

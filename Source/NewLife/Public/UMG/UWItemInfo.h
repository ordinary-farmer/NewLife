// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWItemInfo.generated.h"

class UImage;
class UTextBlock;
class UItem;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWItemInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FLinearColor BorderColor;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* AmountText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ESlateVisibility AmountTextVisibility;
	
public:
	void UpdateInfo(UItem* LinkedItem);
	void UpdateAmountText(UItem* LinkedItem);
};

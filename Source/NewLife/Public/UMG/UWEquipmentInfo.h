// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWEquipmentInfo.generated.h"

class UImage;
class UTextBlock;
class UItem;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWEquipmentInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FLinearColor BorderColor;

public:
	void UpdateInfo(UItem* LinkedItem);
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInventory.generated.h"

class UUWItemHoverInfo;
class UUWPlayerInfo;
class UUWInventoryBag;
class UCanvasPanel;
class UBorder;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWInventory : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UBorder* BackGroundBorder;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ESlateVisibility ItemHoverInfoVisibility;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWItemHoverInfo* ItemHoverInfoWidget;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWInventoryBag* InventoryBagWidget;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWPlayerInfo* PlayerInfoWidget;
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	FEventReply OnBackGroundBorderClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	
public:
	FORCEINLINE void SetItemHoverInfoVisibility(ESlateVisibility NewVisibility) { ItemHoverInfoVisibility = NewVisibility; }
	FORCEINLINE UUWItemHoverInfo* GetItemHoverInfoWidget() const { return ItemHoverInfoWidget; }
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInventorySlot.generated.h"

class UUWItemInfo;
class UItem;
class UUWItemHoverInfo;
class UUWInventory;
class IInventoryInterface;
class UButton;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWInventorySlot : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UUWItemInfo* ItemInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ESlateVisibility ItemInfoVisibility;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UButton* SlotButton;

	bool bSetLinkedItem;

	int32 Index;

	static IInventoryInterface* InventoryInterface;

public:
	UUWInventorySlot(const FObjectInitializer& ObjectInitializer);

	void Activate(UItem* LinkedItem);

	void Deactivate();

	void ChangeAmountText(UItem* LinkedItem);

protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void OnSlotButtonClicked();

public:
	static void SetInventoryInterface(IInventoryInterface* NewInventoryInterface);
	FORCEINLINE void SetIndex(int32 Value) { Index = Value; }
	FORCEINLINE int32 GetIndex() const { return Index; }
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controller/Player/Component/EItemChangeEvent.h"
#include "UWInventoryBag.generated.h"

class UUWInventorySlot;
class UUniformGridPanel;
class IInventoryInterface;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWInventoryBag : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUWInventorySlot> InventorySlotWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category="InventorySlot", meta=(AllowPrivateAccess="true"))
	TArray<UUWInventorySlot*> InventorySlotWidgets;

	UPROPERTY(BlueprintReadOnly, Category="InventorySlot", meta=(AllowPrivateAccess="true", BindWidget))
	UUniformGridPanel* SlotPanel;

	UPROPERTY()
	TScriptInterface<IInventoryInterface> InventoryInterface;

	int32 RowSlotCount;

	int32 ColumnSlotCount;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnItemChanged(int32 SlotIndex, EItemChangeEvent ItemChangeEvent);
};

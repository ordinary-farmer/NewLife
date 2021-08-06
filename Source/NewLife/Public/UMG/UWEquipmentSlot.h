// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Controller/Player/Component/EEquipmentSlot.h"
#include "UWEquipmentSlot.generated.h"

#define WIDGET_SWITCHER_INDEX_EMPTY_SLOT (0)
#define	WIDGET_SWITCHER_INDEX_FULL_SLOT (1)

class UWidgetSwitcher;
class UUWEquipmentInfo;
class UImage;
class UButton;
class UItem;
class UHeroEquipmentComponent;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

	// UPROPERTY()
	// UPlayerInfoComponent* PlayerInfo;
	UPROPERTY()
	UHeroEquipmentComponent* HeroEquipmentComp;
	
	UPROPERTY(meta=(BindWidget))
	UUWEquipmentInfo* EquipmentInfo;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UWidgetSwitcher* SlotWidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UButton* SlotButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UImage* EmptySlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EEquipmentSlot EquipmentSlotType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UTexture2D* EmptySlotImageTexture;
	
public:
	void SetEmptySlotImage(UTexture2D* NewTexture);
	
	void Update();

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void OnSlotButtonClicked();

	bool IsPossibleToInsert(UItem* Item);

public:
	FORCEINLINE void SetEquipmentSlotType(EEquipmentSlot NewType) { EquipmentSlotType = NewType; }
};

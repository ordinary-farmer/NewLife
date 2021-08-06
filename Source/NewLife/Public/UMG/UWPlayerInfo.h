// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controller/Player/Component/EEquipmentSlot.h"
#include "UWPlayerInfo.generated.h"

class UUWEquipmentSlot;
class UButton;
class UUWBasicStatInfo;
class UUWPrimaryStatInfo;
class UUWSecondaryStatInfo;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWPlayerInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* HeadArmorSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* ShoulderArmorSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* TorsoArmorSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* ArmArmorSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* LegArmorSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* NecklaceSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* FirstRingSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* SecondRingSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* RightHandSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUWEquipmentSlot* LeftHandSlot;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UButton* StatInfoButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ESlateVisibility StatInfoVisibility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText StatInfoButtonText;

	static FText RightArrowText;

	static FText LeftArrowText;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStatInfoButtonClicked();

	UFUNCTION()
	void OnEquipmentChanged(EEquipmentSlot EquipmentSlotType);
};

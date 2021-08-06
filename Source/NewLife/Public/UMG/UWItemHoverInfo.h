// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controller/Player/Component/EPrimaryStat.h"
#include "UWItemHoverInfo.generated.h"

class UTextBlock;
class UUniformGridPanel;
class UItem;
class UItemData;
class UEquipmentData;
class UItemManagerSubsystem;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWItemHoverInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* NameText;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UUniformGridPanel* PropertiesPanel;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* CostText;

	FLinearColor NameColor;

	UPROPERTY()
	UTextBlock* RequiredLevelText;

	UPROPERTY()
	UTextBlock* AttackPowerText;

	UPROPERTY()
	UTextBlock* ArmorText;

	UPROPERTY()
	UTextBlock* AbilityDescriptionText;
	
	UPROPERTY()
	TArray<UTextBlock*> EquipmentEffectTexts;
	
	UPROPERTY()
	UTextBlock* DurabilityText;

	UPROPERTY()
	UItemManagerSubsystem* ItemManager;
	
	bool bItemHoverInfoOnItem;

public:
	UUWItemHoverInfo(const FObjectInitializer& ObjectInitializer);

	void Update(UItem* Item);

protected:
	virtual void NativeConstruct() override;
	
private:	
	FText MakeRequiredLevelText(int32 Level);

	FText MakeEquipmentEffectText(const EPrimaryStat EquipmentEffectType, float Value);

	FText MakeAttackPowerText(float MinDamage, float MaxDamage);

	FText MakeArmorText(float Armor);
	
	FText MakeDurabilityText(float Durability, float MaxDurability);

public:	
	FORCEINLINE void SetItemHoverInfoOnItem(bool Value) { bItemHoverInfoOnItem = Value; }
	FORCEINLINE bool GetItemHoverInfoOnItem() const { return bItemHoverInfoOnItem; }
};


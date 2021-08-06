// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWItemHoverInfo.h"
#include "Ability/NLAbility.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Item/DataAsset/ArmorData.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/EquipmentData.h"
#include "Item/DataAsset/ShieldData.h"
#include "Item/DataAsset/WeaponData.h"
#include "Singleton/NLGameInstance.h"
#include "Singleton/ItemManagerSubsystem.h"

UUWItemHoverInfo::UUWItemHoverInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUWItemHoverInfo::Update(UItem* Item)
{
	check(Item);

	UItemData* Data = Item->GetItemData();
	check(Data);

	const FGameplayTag ItemTag = Data->GetItemTag();
	
	PropertiesPanel->ClearChildren();

	NameText->SetText(Data->GetItemName());
	DescriptionText->SetText(Data->GetItemDescription());

	const FSlateColor ItemNameColor(ItemManager->GetItemColor(Data));
	NameText->SetColorAndOpacity(ItemNameColor);

	int32 PropertiesRowIndex = 0;
	
	if (ItemTag.MatchesTag(ITEM_TAG_EQUIPMENT))
	{
		UEquipmentData* EquipmentData = Cast<UEquipmentData>(Data);
		check(EquipmentData);		

		RequiredLevelText->SetText(MakeRequiredLevelText(EquipmentData->GetRequiredLevel()));
		PropertiesPanel->AddChildToUniformGrid(RequiredLevelText, PropertiesRowIndex++, 0);

		if (ItemTag.MatchesTag(ITEM_TAG_WEAPON))
		{
			UWeaponData* WeaponData = Cast<UWeaponData>(EquipmentData);
			check(WeaponData);

			AttackPowerText->SetText(MakeAttackPowerText(WeaponData->GetMinDamage(), WeaponData->GetMaxDamage()));
			PropertiesPanel->AddChildToUniformGrid(AttackPowerText, PropertiesRowIndex++, 0);
		}

		if (ItemTag.MatchesTag(ITEM_TAG_SHIELD))
		{
			UShieldData* ShieldData = Cast<UShieldData>(EquipmentData);
			check(ShieldData);

			ArmorText->SetText(MakeArmorText(ShieldData->GetArmor()));
			PropertiesPanel->AddChildToUniformGrid(ArmorText, PropertiesRowIndex++, 0);
		}

		if (ItemTag.MatchesTag(ITEM_TAG_ARMOR))
		{
			UArmorData* ArmorData = Cast<UArmorData>(EquipmentData);
			check(ArmorData);

			ArmorText->SetText(MakeArmorText(ArmorData->GetArmor()));
			PropertiesPanel->AddChildToUniformGrid(ArmorText, PropertiesRowIndex++, 0);
		}

		for (int32 i = 0; i < static_cast<int32>(EPrimaryStat::MaxCount); ++i)
		{
			const EPrimaryStat EquipmentEffectType = static_cast<EPrimaryStat>(i);

			if (EquipmentData->GetEquipmentEffects().Contains(EquipmentEffectType))
			{
				float EffectValue = *EquipmentData->GetEquipmentEffects().Find(EquipmentEffectType);

				EquipmentEffectTexts[i]->SetText(MakeEquipmentEffectText(EquipmentEffectType, EffectValue));
				PropertiesPanel->AddChildToUniformGrid(EquipmentEffectTexts[i], PropertiesRowIndex++, 0);
			}
		}

		if(ItemTag.MatchesTag(ITEM_TAG_DURABLE_EQUIPMENT))
		{
			UDurableEquipmentData* DurableEquipmentData = Cast<UDurableEquipmentData>(EquipmentData);
			check(DurableEquipmentData);

			DurabilityText->SetText(MakeDurabilityText(Item->GetDurability(), DurableEquipmentData->GetMaxDurability()));
			PropertiesPanel->AddChildToUniformGrid(DurabilityText, PropertiesRowIndex, 0);
		}
	}

	UNLAbility* Ability = Data->GetAbility();

	if(Ability)
	{
		AbilityDescriptionText->SetText(Ability->GetAbilityDescription());
		PropertiesPanel->AddChildToUniformGrid(AbilityDescriptionText, PropertiesRowIndex++, 0);
	}	
}

void UUWItemHoverInfo::NativeConstruct()
{
	Super::NativeConstruct();

	RequiredLevelText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	RequiredLevelText->Font.Size = 8;

	AttackPowerText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	AttackPowerText->Font.Size = 12;

	ArmorText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	ArmorText->Font.Size = 12;

	const FSlateColor EffectColor(FLinearColor(0.f, 1.f, 0.f));

	AbilityDescriptionText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	AbilityDescriptionText->Font.Size = 8;
	AbilityDescriptionText->SetColorAndOpacity(EffectColor);

	for (int32 i = 0; i < static_cast<int32>(EPrimaryStat::MaxCount); ++i)
	{
		UTextBlock* NewTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		NewTextBlock->Font.Size = 8;
		NewTextBlock->SetColorAndOpacity(EffectColor);

		EquipmentEffectTexts.Emplace(NewTextBlock);
	}
	
	Visibility = ESlateVisibility::Hidden;

	DurabilityText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	DurabilityText->Font.Size = 8;

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		ItemManager = GameInstance->GetSubsystem<UItemManagerSubsystem>();
	}
}

FText UUWItemHoverInfo::MakeRequiredLevelText(int32 Level)
{
	static const FString Prefix(TEXT("최소 요구 레벨 "));

	const FString Result = Prefix + FString::FromInt(Level);

	return FText::FromString(Result);
}

FText UUWItemHoverInfo::MakeEquipmentEffectText(const EPrimaryStat EquipmentEffectType, float Value)
{
	static const FString StrengthPrefix(TEXT("힘 +"));
	static const FString DexterityPrefix(TEXT("민첩 +"));
	static const FString VitalityPrefix(TEXT("활력 +"));
	static const FString IntelligencePrefix(TEXT("지능 +"));

	FString Result;

	switch (EquipmentEffectType)
	{
	case EPrimaryStat::Strength:
		Result = StrengthPrefix + FString::FromInt(Value);
		break;
	case EPrimaryStat::Dexterity:
		Result = DexterityPrefix + FString::FromInt(Value);
		break;
	case EPrimaryStat::Vitality:
		Result = VitalityPrefix + FString::FromInt(Value);
		break;
	case EPrimaryStat::Intelligence:
		Result = IntelligencePrefix + FString::FromInt(Value);
		break;
	default:
		checkNoEntry();
	}

	return FText::FromString(Result);
}

FText UUWItemHoverInfo::MakeAttackPowerText(float MinDamage, float MaxDamage)
{
	static const FString WeaponPrefix(TEXT("공격력 "));
	static const FString DamageTilde(TEXT(" To "));

	const FString Result = WeaponPrefix + FString::FromInt(MinDamage) + DamageTilde + FString::FromInt(MaxDamage);

	return FText::FromString(Result);
}

FText UUWItemHoverInfo::MakeArmorText(float Armor)
{
	static const FString ArmorPrefix(TEXT("방어도 "));

	const FString Result = ArmorPrefix + FString::FromInt(Armor);

	return FText::FromString(Result);
}

FText UUWItemHoverInfo::MakeDurabilityText(float Durability, float MaxDurability)
{
	static const FString DurabilityPrefix(TEXT("내구도 "));

	const FString Result = DurabilityPrefix + FString::FromInt(Durability) + FString(" / ") +
		FString::FromInt(MaxDurability);

	return FText::FromString(Result);
}

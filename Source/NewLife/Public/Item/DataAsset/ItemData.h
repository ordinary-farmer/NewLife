// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EItemTier.h"
#include "ItemData.generated.h"

#define ITEM_TAG_EQUIPMENT (FGameplayTag::RequestGameplayTag("Item.Equipment"))
#define ITEM_TAG_ACCESSORY (FGameplayTag::RequestGameplayTag("Item.Equipment.Accessory"))
#define ITEM_TAG_DURABLE_EQUIPMENT (FGameplayTag::RequestGameplayTag("Item.Equipment.DurableEquipment"))
#define ITEM_TAG_ARMOR (FGameplayTag::RequestGameplayTag("Item.Equipment.DurableEquipment.Armor"))
#define ITEM_TAG_WEAPON (FGameplayTag::RequestGameplayTag("Item.Equipment.DurableEquipment.Weapon"))
#define ITEM_TAG_MAIN_WEAPON (FGameplayTag::RequestGameplayTag("Item.Equipment.DurableEquipment.Weapon.MainWeapon"))
#define ITEM_TAG_SHIELD (FGameplayTag::RequestGameplayTag("Item.Equipment.DurableEquipment.Weapon.Shield"))
#define ITEM_TAG_POTION (FGameplayTag::RequestGameplayTag("Item.Potion"))

class UNLAbility;
class UItemManagerSubsystem;

UCLASS(HideDropdown)
class NEWLIFE_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	FPrimaryAssetType PrimaryAssetType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemTier ItemTier;

	bool bIsCountable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxAmount;

	bool bHasAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UNLAbility> AbilityClass;

	// 아이템 데이터가 로드된 시점에 ItemAbility가 nullptr이면 새로 생성하고 할당
	UPROPERTY()
	UNLAbility* Ability;

public:
	UItemData();

private:
	virtual bool CanEditChange(const FProperty* InProperty) const override;

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	FORCEINLINE int32 GetMaxAmount() const { return MaxAmount; }

	FORCEINLINE FText GetItemName() const { return ItemName; }

	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }

	FORCEINLINE UTexture2D* GetItemIcon() const { return ItemIcon; }

	FORCEINLINE EItemTier GetItemTier() const { return ItemTier; }

	FORCEINLINE bool IsCountable() const { return bIsCountable; }

	UNLAbility* GetAbility();

	virtual FGameplayTag GetItemTag() PURE_VIRTUAL(UItemData::GetItemTag, return FGameplayTag(););
};

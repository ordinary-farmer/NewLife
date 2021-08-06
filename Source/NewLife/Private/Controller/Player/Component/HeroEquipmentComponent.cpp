// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Controller/Player/Component/HeroEquipmentComponent.h"
#include "Item/Object/Item.h"
#include "Item/DataAsset/ItemData.h"
#include "Item/DataAsset/AccessoryData.h"
#include "Item/DataAsset/ArmorData.h"
#include "GameplayTagContainer.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"
#include "Item/DataAsset/ShieldData.h"
#include "Pawn/Player/Hero/Hero.h"


UHeroEquipmentComponent::UHeroEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	for (int i = 0; i < static_cast<int32>(EEquipmentSlot::MaxCount); ++i)
	{
		Equipments.Emplace(static_cast<EEquipmentSlot>(i), nullptr);
	}
}

UItem* UHeroEquipmentComponent::GetEquipment(EEquipmentSlot EquipmentSlotType)
{
	return *Equipments.Find(EquipmentSlotType);
}

void UHeroEquipmentComponent::InsertItem(EEquipmentSlot EquipmentSlotType, UItem* Item)
{
	Equipments.Add(EquipmentSlotType, Item);

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwner());
	check(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();
	check(HeroStatComp);

	UEquipmentData* EquipmentData = Cast<UEquipmentData>((*Equipments.Find(EquipmentSlotType))->GetItemData());
	HeroStatComp->ApplyEquipEffect(EEquipType::Equip, EquipmentData);

	FGameplayTag ItemTag = EquipmentData->GetItemTag();

	AHero* PlayerCharacter = Cast<AHero>(PlayerController->GetPawn());
	check(PlayerCharacter);

	if (ItemTag.MatchesTag(ITEM_TAG_WEAPON))
	{
		UWeaponData* WeaponData = Cast<UWeaponData>(EquipmentData);
		check(WeaponData);

		HeroStatComp->ApplyWeaponDamage(EEquipType::Equip, WeaponData);

		if (ItemTag.MatchesTag(ITEM_TAG_SHIELD))
		{
			UShieldData* ShieldData = Cast<UShieldData>(WeaponData);
			check(ShieldData);

			HeroStatComp->ApplyShieldArmor(EEquipType::Equip, ShieldData);
		}

		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::RightHand:
			PlayerCharacter->SetRightHandWeaponMesh(WeaponData->GetLoadedBody());
			break;
		case EEquipmentSlot::LeftHand:
			PlayerCharacter->SetLeftHandWeaponMesh(WeaponData->GetLoadedBody());
			break;
		default:
			checkNoEntry();
		}
	}
	else if (ItemTag.MatchesTag(ITEM_TAG_ARMOR))
	{
		UArmorData* ArmorData = Cast<UArmorData>(EquipmentData);
		check(ArmorData);

		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::HeadArmor:
			PlayerCharacter->SetHeadMesh(ArmorData->GetLoadedBody());
			break;
		case EEquipmentSlot::ShoulderArmor:
			PlayerCharacter->SetShoulderMesh(ArmorData->GetLoadedBody());
			break;
		case EEquipmentSlot::TorsoArmor:
			PlayerCharacter->SetTorsoMesh(ArmorData->GetLoadedBody());
			break;
		case EEquipmentSlot::ArmArmor:
			PlayerCharacter->SetArmMesh(ArmorData->GetLoadedBody());
			break;
		case EEquipmentSlot::LegArmor:
			PlayerCharacter->SetLegMesh(ArmorData->GetLoadedBody());
			break;
		default:
			checkNoEntry();
		}
	}

	if(OnEquipmentChanged.IsBound())
	{
		OnEquipmentChanged.Broadcast(EquipmentSlotType);
	}
}

UItem* UHeroEquipmentComponent::ReleaseItem(EEquipmentSlot EquipmentSlotType)
{
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwner());
	check(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();
	check(HeroStatComp);

	UEquipmentData* EquipmentData = Cast<UEquipmentData>((*Equipments.Find(EquipmentSlotType))->GetItemData());
	HeroStatComp->ApplyEquipEffect(EEquipType::UnEquip, EquipmentData);

	FGameplayTag ItemTag = EquipmentData->GetItemTag();

	AHero* PlayerCharacter = Cast<AHero>(PlayerController->GetPawn());
	check(PlayerCharacter);
	
	if (ItemTag.MatchesTag(ITEM_TAG_WEAPON))
	{
		UWeaponData* WeaponData = Cast<UWeaponData>(EquipmentData);
		check(WeaponData);

		HeroStatComp->ApplyWeaponDamage(EEquipType::UnEquip, WeaponData);

		if (ItemTag.MatchesTag(ITEM_TAG_SHIELD))
		{
			UShieldData* ShieldData = Cast<UShieldData>(WeaponData);
			check(ShieldData);

			HeroStatComp->ApplyShieldArmor(EEquipType::UnEquip, ShieldData);
		}

		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::RightHand:
			PlayerCharacter->SetRightHandWeaponMesh(nullptr);
			break;
		case EEquipmentSlot::LeftHand:
			PlayerCharacter->SetLeftHandWeaponMesh(nullptr);
			break;
		default:
			checkNoEntry();
		}
	}
	else if (ItemTag.MatchesTag(ITEM_TAG_ARMOR))
	{
		switch (EquipmentSlotType)
		{
		case EEquipmentSlot::HeadArmor:
			PlayerCharacter->SetHeadMesh(nullptr);
			break;
		case EEquipmentSlot::ShoulderArmor:
			PlayerCharacter->SetShoulderMesh(nullptr);
			break;
		case EEquipmentSlot::TorsoArmor:
			PlayerCharacter->SetTorsoMesh(nullptr);
			break;
		case EEquipmentSlot::ArmArmor:
			PlayerCharacter->SetArmMesh(nullptr);
			break;
		case EEquipmentSlot::LegArmor:
			PlayerCharacter->SetLegMesh(nullptr);
			break;
		default:
			checkNoEntry();
		}
	}
	
	// 언이큅하고 형상변환해야함
	UItem* Result = *Equipments.Find(EquipmentSlotType);
	Equipments.Add(EquipmentSlotType, nullptr);

	if(OnEquipmentChanged.IsBound())
	{
		OnEquipmentChanged.Broadcast(EquipmentSlotType);
	}
	
	return Result;
}

void UHeroEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

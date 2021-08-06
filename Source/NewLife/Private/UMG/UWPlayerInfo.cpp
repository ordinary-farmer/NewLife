// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWPlayerInfo.h"
#include "Components/Button.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroEquipmentComponent.h"
#include "UMG/UWEquipmentSlot.h"

FText UUWPlayerInfo::RightArrowText = FText::FromString(">");
FText UUWPlayerInfo::LeftArrowText = FText::FromString("<");

void UUWPlayerInfo::NativeConstruct()
{	
	StatInfoButton->OnClicked.AddDynamic(this, &UUWPlayerInfo::OnStatInfoButtonClicked);
	
	StatInfoVisibility = ESlateVisibility::Hidden;
	StatInfoButtonText = RightArrowText;

	ANLPlayerController* PC = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PC);

	UHeroEquipmentComponent* HeroEquipmentComp = PC->GetHeroEquipmentComp();
	check(HeroEquipmentComp);

	HeroEquipmentComp->OnEquipmentChanged.AddDynamic(this, &UUWPlayerInfo::UUWPlayerInfo::OnEquipmentChanged);
}

void UUWPlayerInfo::OnStatInfoButtonClicked()
{
	if(StatInfoVisibility == ESlateVisibility::HitTestInvisible)
	{
		StatInfoVisibility = ESlateVisibility::Hidden;
		StatInfoButtonText = RightArrowText;
	}
	else if(StatInfoVisibility == ESlateVisibility::Hidden)
	{
		StatInfoVisibility = ESlateVisibility::HitTestInvisible;
		StatInfoButtonText = LeftArrowText;
	}
}

void UUWPlayerInfo::OnEquipmentChanged(EEquipmentSlot EquipmentSlotType)
{
	switch (EquipmentSlotType)
	{
		case EEquipmentSlot::HeadArmor:
			HeadArmorSlot->Update();
			break;
		case EEquipmentSlot::ShoulderArmor:
			ShoulderArmorSlot->Update();
			break;
		case EEquipmentSlot::TorsoArmor:
			TorsoArmorSlot->Update();
			break;
		case EEquipmentSlot::LegArmor:
			LegArmorSlot->Update();
			break;
		case EEquipmentSlot::ArmArmor:
			ArmArmorSlot->Update();
			break;
		case EEquipmentSlot::Necklace:
			NecklaceSlot->Update();
			break;
		case EEquipmentSlot::FirstRing:
			FirstRingSlot->Update();
			break;
		case EEquipmentSlot::SecondRing:
			SecondRingSlot->Update();
			break;
		case EEquipmentSlot::RightHand:
			RightHandSlot->Update();
			break;
		case EEquipmentSlot::LeftHand:
			LeftHandSlot->Update();
			break;
		default:
			checkNoEntry();
	}
}

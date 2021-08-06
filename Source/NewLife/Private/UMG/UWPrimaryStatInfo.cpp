// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWPrimaryStatInfo.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"

void UUWPrimaryStatInfo::NativePreConstruct()
{
	Super::NativePreConstruct();

	StatName->SetText(StatNameText);
	StatButton->SetIsEnabled(false);
}

void UUWPrimaryStatInfo::NativeConstruct()
{
	Super::NativeConstruct();

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();
	check(HeroStatComp);

	OnStatChanged(HeroStatComp->GetPrimaryStat(PrimaryStatType));

	switch (PrimaryStatType)
	{
	case EPrimaryStat::Strength:
		HeroStatComp->OnStrengthChanged.AddDynamic(this, &UUWPrimaryStatInfo::OnStatChanged);
		break;
	case EPrimaryStat::Dexterity:
		HeroStatComp->OnDexterityChanged.AddDynamic(this, &UUWPrimaryStatInfo::OnStatChanged);
		break;
	case EPrimaryStat::Vitality:
		HeroStatComp->OnVitalityChanged.AddDynamic(this, &UUWPrimaryStatInfo::OnStatChanged);
		break;
	case EPrimaryStat::Intelligence:
		HeroStatComp->OnIntelligenceChanged.AddDynamic(this, &UUWPrimaryStatInfo::OnStatChanged);
		break;
	default:
		checkNoEntry();
	}

	HeroStatComp->OnAvailableStatPointChanged.AddDynamic(this, &UUWPrimaryStatInfo::OnAvailableStatChanged);
}

void UUWPrimaryStatInfo::OnStatChanged(int32 Value)
{
	StatNumber->SetText(FText::AsNumber(Value));
}

void UUWPrimaryStatInfo::OnButtonClicked()
{
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();
	check(HeroStatComp);

	HeroStatComp->UseAvailableStatPoint(PrimaryStatType);
}

void UUWPrimaryStatInfo::OnAvailableStatChanged(int32 Value)
{
	if (Value == 0)
	{
		StatButton->SetIsEnabled(false);
	}

	StatButton->SetIsEnabled(true);
}

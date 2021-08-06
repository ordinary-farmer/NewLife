// Made By Park Joo Hyeong. This is my first Portfollio.

#include "UMG/UWSecondaryStatInfo.h"
#include "Components/TextBlock.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"

void UUWSecondaryStatInfo::NativePreConstruct()
{
	Super::NativePreConstruct();

	StatName->SetText(StatNameText);
}

void UUWSecondaryStatInfo::NativeConstruct()
{
	Super::NativeConstruct();

	FloatNumberFormattingOptions.SetMaximumFractionalDigits(MaximumFractionalDigits);

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();
	check(HeroStatComp);

	OnStatChanged(HeroStatComp->GetSecondaryStat(SecondaryStatType));

	switch (SecondaryStatType)
	{
	case ESecondaryStat::DefensePower:
		HeroStatComp->OnDefensePowerChanged.AddDynamic(this, &UUWSecondaryStatInfo::OnStatChanged);
		break;
	case ESecondaryStat::MinDamage:
		HeroStatComp->OnMinDamageChanged.AddDynamic(this, &UUWSecondaryStatInfo::OnStatChanged);
		break;
	case ESecondaryStat::MaxDamage:
		HeroStatComp->OnMaxDamageChanged.AddDynamic(this, &UUWSecondaryStatInfo::OnStatChanged);
		break;
	case ESecondaryStat::MaxHealthPoint:
		break;
	case ESecondaryStat::HealthPointRecoveryRate:
		HeroStatComp->OnHealthPointRecoveryRateChanged.AddDynamic(this, &UUWSecondaryStatInfo::OnStatChanged);
		break;
	case ESecondaryStat::MaxManaPoint:
		break;
	case ESecondaryStat::ManaPointRecoveryRate:
		HeroStatComp->OnManaPointRecoveryRateChanged.AddDynamic(this, &UUWSecondaryStatInfo::OnStatChanged);
		break;
	case ESecondaryStat::CriticalHitProbability:
		HeroStatComp->OnCriticalHitProbabilityChanged.AddDynamic(this, &UUWSecondaryStatInfo::OnStatChanged);
		break;
	default:
		checkNoEntry();
	}
}

void UUWSecondaryStatInfo::OnStatChanged(float Value)
{
	StatNumber->SetText(FText::AsNumber(Value, &FloatNumberFormattingOptions));
}

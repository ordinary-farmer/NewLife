// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWManaBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"

void UUWManaBar::NativeConstruct()
{
	ANLPlayerController* PC = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PC);

	HeroStatComp = PC->GetHeroStatComp();
	check(HeroStatComp);

	HeroStatComp->OnCurrentManaPointChanged.AddDynamic(this, &UUWManaBar::OnCurrentManaPointChanged);
	HeroStatComp->OnMaxManaPointChanged.AddDynamic(this, &UUWManaBar::OnMaxManaPointChanged);

	OnMaxManaPointChanged(HeroStatComp->GetSecondaryStat(ESecondaryStat::MaxManaPoint));
	OnCurrentManaPointChanged(HeroStatComp->GetCurrentManaPoint());
}

void UUWManaBar::OnCurrentManaPointChanged(float Value)
{
	FNumberFormattingOptions Opts;
	Opts.MaximumFractionalDigits = 0;
	
	CurrentManaPoint->SetText(FText::AsNumber(Value, &Opts));

	ManaBar->SetPercent(Value / HeroStatComp->GetSecondaryStat(ESecondaryStat::MaxManaPoint));
}

void UUWManaBar::OnMaxManaPointChanged(float Value)
{
	FNumberFormattingOptions Opts;
	Opts.MaximumFractionalDigits = 0;

	MaxManaPoint->SetText(FText::AsNumber(Value, &Opts));

	ManaBar->SetPercent(HeroStatComp->GetCurrentManaPoint() / Value);
}

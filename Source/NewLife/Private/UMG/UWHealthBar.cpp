// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWHealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"

void UUWHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	ANLPlayerController* PC = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PC);

	HeroStatComp = PC->GetHeroStatComp();
	check(HeroStatComp);

	HeroStatComp->OnCurrentHealthPointChanged.AddDynamic(this, &UUWHealthBar::OnCurrentHealthPointChanged);
	HeroStatComp->OnMaxHealthPointChanged.AddDynamic(this, &UUWHealthBar::OnMaxHealthPointChanged);

	OnMaxHealthPointChanged(HeroStatComp->GetSecondaryStat(ESecondaryStat::MaxHealthPoint));
	OnCurrentHealthPointChanged(HeroStatComp->GetCurrentHealthPoint());
}

void UUWHealthBar::OnCurrentHealthPointChanged(float Value)
{
	FNumberFormattingOptions Opts;
	Opts.MaximumFractionalDigits = 0;
	
	CurrentHealthPoint->SetText(FText::AsNumber(Value, &Opts));

	HealthBar->SetPercent(Value / HeroStatComp->GetSecondaryStat(ESecondaryStat::MaxHealthPoint));
}

void UUWHealthBar::OnMaxHealthPointChanged(float Value)
{
	FNumberFormattingOptions Opts;
	Opts.MaximumFractionalDigits = 0;

	MaxHealthPoint->SetText(FText::AsNumber(Value, &Opts));

	HealthBar->SetPercent(HeroStatComp->GetCurrentHealthPoint() / Value);
}

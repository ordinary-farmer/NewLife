// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWBasicStatInfo.h"
#include "Components/TextBlock.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"

void UUWBasicStatInfo::NativeConstruct()
{
	Super::NativeConstruct();

	FloatNumberFormattingOptions.MaximumFractionalDigits = 2;

	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(GetOwningPlayer());
	check(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();
	check(HeroStatComp);

	OnLevelChanged(HeroStatComp->GetLevel());
	OnExperienceChanged(HeroStatComp->GetExperiencePoint());
	OnMaxExperienceChanged(HeroStatComp->GetMaxExperiencePoint());
	OnAvailableStatPointChanged(HeroStatComp->GetAvailableStatPoint());

	HeroStatComp->OnLevelChanged.AddDynamic(this, &UUWBasicStatInfo::OnLevelChanged);
	HeroStatComp->OnExperiencePointChanged.AddDynamic(this, &UUWBasicStatInfo::OnExperienceChanged);
	HeroStatComp->OnMaxExperiencePointChanged.AddDynamic(this, &UUWBasicStatInfo::OnMaxExperienceChanged);
	HeroStatComp->OnAvailableStatPointChanged.AddDynamic(this, &UUWBasicStatInfo::OnAvailableStatPointChanged);
}

void UUWBasicStatInfo::OnLevelChanged(int32 Value)
{
	LevelNumber->SetText(FText::AsNumber(Value));
}

void UUWBasicStatInfo::OnExperienceChanged(float Value)
{
	ExperienceNumber->SetText(FText::AsNumber(Value, &FloatNumberFormattingOptions));
}

void UUWBasicStatInfo::OnMaxExperienceChanged(float Value)
{
	MaxExperienceNumber->SetText(FText::AsNumber(Value, &FloatNumberFormattingOptions));
}

void UUWBasicStatInfo::OnAvailableStatPointChanged(int32 Value)
{
	AvailableStatPointNumber->SetText(FText::AsNumber(Value));
}

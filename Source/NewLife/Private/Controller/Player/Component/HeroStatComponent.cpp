// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Controller/Player/Component/HeroStatComponent.h"
#include "Item/DataAsset/EquipmentData.h"
#include "Item/DataAsset/ShieldData.h"
#include "Item/DataAsset/WeaponData.h"
#include "TableRowBase/FExperiencePointPerLevel.h"
#include "UMG/UWPrimaryStatInfo.h"

UHeroStatComponent::UHeroStatComponent()
	: CriticalHitProbability(1.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> ExperienceDTAsset(
		TEXT("DataTable'/Game/_NewLife/DataTable/ExperienceTable.ExperienceTable'"));
	if (ExperienceDTAsset.Succeeded())
	{
		ExperienceDataTable = ExperienceDTAsset.Object;
	}
}

void UHeroStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AddOrSubCurrentHealthPoint(HealthPointRecoveryRate / 60 * DeltaTime);
	AddOrSubCurrentManaPoint(ManaPointRecoveryRate / 60 * DeltaTime);
}

void UHeroStatComponent::IncreaseExperiencePoint(float Value)
{
	ExperiencePoint += Value;

	if (ExperiencePoint >= MaxExperiencePoint)
	{
		IncreaseLevel();
	}

	if(OnExperiencePointChanged.IsBound())
	{
		OnExperiencePointChanged.Broadcast(ExperiencePoint);
	}
}

void UHeroStatComponent::UseAvailableStatPoint(EPrimaryStat PrimaryStatType)
{
	check(AvailableStatPoint > 0);
	
	AddOrSubStatByType(PrimaryStatType, 1);

	AvailableStatPoint -= 1;

	if(OnAvailableStatPointChanged.IsBound())
	{
		OnAvailableStatPointChanged.Broadcast(AvailableStatPoint);
	}
}

void UHeroStatComponent::ApplyEquipEffect(EEquipType EquipType, UEquipmentData* EquipmentData)
{
	const int32 Coefficient = EquipType == EEquipType::Equip ? 1 : -1;
	
	for (const auto Effect : EquipmentData->GetEquipmentEffects())
	{
		AddOrSubStatByType(Effect.Key, Coefficient * Effect.Value);
	}
}

void UHeroStatComponent::ApplyWeaponDamage(EEquipType EquipType, UWeaponData* WeaponData)
{
	const int32 Coefficient = EquipType == EEquipType::Equip ? 1 : -1;

	AddOrSubMinDamage(Coefficient * WeaponData->GetMinDamage());
	AddOrSubMaxDamage(Coefficient * WeaponData->GetMaxDamage());
}

void UHeroStatComponent::ApplyShieldArmor(EEquipType EquipType, UShieldData* ShieldData)
{
	const int32 Coefficient = EquipType == EEquipType::Equip ? 1 : -1;

	AddOrSubDefensePower(Coefficient * ShieldData->GetArmor());
}

void UHeroStatComponent::RecoverHealth(float Value)
{
	CurrentHealthPoint = CurrentHealthPoint + Value > MaxHealthPoint ? MaxHealthPoint : CurrentHealthPoint + Value;

	if(OnCurrentHealthPointChanged.IsBound())
	{
		OnCurrentHealthPointChanged.Broadcast(CurrentHealthPoint);
	}
}

void UHeroStatComponent::GetDamage(float Value)
{
	CurrentHealthPoint = CurrentHealthPoint - Value < 0.f ? 0.f : CurrentHealthPoint - Value;

	if(OnCurrentHealthPointChanged.IsBound())
	{
		OnCurrentHealthPointChanged.Broadcast(CurrentHealthPoint);
	}	
}

void UHeroStatComponent::RecoverMana(float Value)
{
	CurrentManaPoint = CurrentManaPoint + Value > MaxManaPoint ? MaxManaPoint : CurrentManaPoint + Value;

	if(OnCurrentManaPointChanged.IsBound())
	{
		OnCurrentManaPointChanged.Broadcast(CurrentManaPoint);
	}
}

void UHeroStatComponent::UseMana(float Value)
{
	CurrentManaPoint = CurrentManaPoint - Value < 0.f ? 0.f : CurrentManaPoint - Value;

	if(OnCurrentManaPointChanged.IsBound())
	{
		OnCurrentManaPointChanged.Broadcast(CurrentManaPoint);
	}
}

int32 UHeroStatComponent::GetPrimaryStat(EPrimaryStat PrimaryStatType)
{
	int32 Result = 0;

	switch (PrimaryStatType)
	{
	case EPrimaryStat::Strength:
		Result = Strength;
		break;
	case EPrimaryStat::Dexterity:
		Result = Dexterity;
		break;
	case EPrimaryStat::Vitality:
		Result = Vitality;
		break;
	case EPrimaryStat::Intelligence:
		Result = Intelligence;
		break;
	default:
		checkNoEntry();
	}

	return Result;
}

float UHeroStatComponent::GetSecondaryStat(ESecondaryStat SecondaryStatType)
{
	float Result = 0.f;

	switch (SecondaryStatType)
	{
	case ESecondaryStat::DefensePower:
		Result = DefensePower;
		break;
	case ESecondaryStat::MinDamage:
		Result = MinDamage;
		break;
	case ESecondaryStat::MaxDamage:
		Result = MaxDamage;
		break;
	case ESecondaryStat::MaxHealthPoint:
		Result = MaxHealthPoint;
		break;
	case ESecondaryStat::HealthPointRecoveryRate:
		Result = HealthPointRecoveryRate;
		break;
	case ESecondaryStat::MaxManaPoint:
		Result = MaxManaPoint;
		break;
	case ESecondaryStat::ManaPointRecoveryRate:
		Result = ManaPointRecoveryRate;
		break;
	case ESecondaryStat::CriticalHitProbability:
		Result = CriticalHitProbability;
		break;
	default:
		checkNoEntry();
	}

	return Result;
}

void UHeroStatComponent::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;

	AddOrSubStrength(INITIAL_STRENGTH);
	AddOrSubDexterity(INITIAL_DEXTERITY);
	AddOrSubVitality(INITIAL_VITALITY);
	AddOrSubIntelligence(INITIAL_INTELLIGENCE);

	CurrentHealthPoint = MaxHealthPoint;
	CurrentManaPoint = MaxManaPoint;
	
	InitializeExperiencePoint(Level);
}

void UHeroStatComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnLevelChanged.Clear();
	OnExperiencePointChanged.Clear();
	OnMaxExperiencePointChanged.Clear();
	OnAvailableStatPointChanged.Clear();
	OnStrengthChanged.Clear();
	OnDexterityChanged.Clear();
	OnVitalityChanged.Clear();
	OnIntelligenceChanged.Clear();
	OnDefensePowerChanged.Clear();
	OnMinDamageChanged.Clear();
	OnMaxDamageChanged.Clear();
	OnMaxHealthPointChanged.Clear();
	OnHealthPointRecoveryRateChanged.Clear();
	OnMaxManaPointChanged.Clear();
	OnManaPointRecoveryRateChanged.Clear();
	OnCriticalHitProbabilityChanged.Clear();
}

void UHeroStatComponent::IncreaseLevel()
{
	//
	Level += 1;

	if(OnLevelChanged.IsBound())
	{
		OnLevelChanged.Broadcast(Level);
	}

	IncreaseAvailableStatPoint(DEFAULT_AVAILABLE_STAT_POINT_INCREMENT);
	InitializeExperiencePoint(Level);
}

void UHeroStatComponent::IncreaseAvailableStatPoint(int32 Value)
{
	AvailableStatPoint += Value;

	if(OnAvailableStatPointChanged.IsBound())
	{
		OnAvailableStatPointChanged.Broadcast(Value);
	}
}

void UHeroStatComponent::InitializeExperiencePoint(int32 NewLevel)
{
	check(NewLevel <= MAX_LEVEL);

	static const FString LevelPrefix("Level");

	FExperiencePointPerLevel* Row = ExperienceDataTable->FindRow<FExperiencePointPerLevel>(
		*(LevelPrefix + FString::FromInt(NewLevel)), TEXT(""));
	checkf(Row, TEXT("Find Row Failed : %s"), *ExperienceDataTable->GetName());

	ExperiencePoint -= MaxExperiencePoint;
	MaxExperiencePoint = Row->MaxExperiencePoint;

	if(OnMaxExperiencePointChanged.IsBound())
	{
		OnMaxExperiencePointChanged.Broadcast(MaxExperiencePoint);
	}
}

void UHeroStatComponent::AddOrSubStatByType(EPrimaryStat PrimaryStatType, int32 Value)
{
	switch (PrimaryStatType)
	{
	case EPrimaryStat::Strength:
		AddOrSubStrength(Value);
		break;
	case EPrimaryStat::Dexterity:
		AddOrSubDexterity(Value);
		break;
	case EPrimaryStat::Vitality:
		AddOrSubVitality(Value);
		break;
	case EPrimaryStat::Intelligence:
		AddOrSubIntelligence(Value);
		break;
	default:
		checkNoEntry();
	}
}

void UHeroStatComponent::AddOrSubStrength(int32 Value)
{
	Strength += Value;

	AddOrSubMinDamage(Value * 2.f);
	AddOrSubMaxDamage(Value * 2.f);

	if(OnStrengthChanged.IsBound())
	{
		OnStrengthChanged.Broadcast(Strength);
	}
}

void UHeroStatComponent::AddOrSubDexterity(int32 Value)
{
	Dexterity += Value;

	AddOrSubDefensePower(Value * .5f);
	AddOrSubCriticalHitProbability(Value * .02f);

	if(OnDexterityChanged.IsBound())
	{
		OnDexterityChanged.Broadcast(Dexterity);
	}	
}

void UHeroStatComponent::AddOrSubVitality(int32 Value)
{
	Vitality += Value;

	AddOrSubMaxHealthPoint(Value * 1.5f);
	AddOrSubHealthPointRecoveryRate(Value * .2f);

	if(OnVitalityChanged.IsBound())
	{
		OnVitalityChanged.Broadcast(Vitality);
	}
}

void UHeroStatComponent::AddOrSubIntelligence(int32 Value)
{
	Intelligence += Value;

	AddOrSubMaxManaPoint(Value * 1.2f);
	AddOrSubManaPointRecoveryRate(Value * .2f);

	if(OnIntelligenceChanged.IsBound())
	{
		OnIntelligenceChanged.Broadcast(Intelligence);
	}
}

void UHeroStatComponent::AddOrSubDefensePower(float Value)
{
	DefensePower += Value;

	if(OnDefensePowerChanged.IsBound())
	{
		OnDefensePowerChanged.Broadcast(DefensePower);
	}
}

void UHeroStatComponent::AddOrSubMinDamage(float Value)
{
	MinDamage += Value;

	if(OnMinDamageChanged.IsBound())
	{
		OnMinDamageChanged.Broadcast(MinDamage);
	}
}

void UHeroStatComponent::AddOrSubMaxDamage(float Value)
{
	MaxDamage += Value;

	if(OnMaxDamageChanged.IsBound())
	{
		OnMaxDamageChanged.Broadcast(MaxDamage);
	}
}

void UHeroStatComponent::AddOrSubMaxHealthPoint(float Value)
{
	MaxHealthPoint += Value;

	if(OnMaxHealthPointChanged.IsBound())
	{
		OnMaxHealthPointChanged.Broadcast(MaxHealthPoint);
	}
}

void UHeroStatComponent::AddOrSubCurrentHealthPoint(float Value)
{
	CurrentHealthPoint = CurrentHealthPoint + Value > MaxHealthPoint ? MaxHealthPoint : CurrentHealthPoint + Value;
	OnCurrentHealthPointChanged.Broadcast(CurrentHealthPoint);
}

void UHeroStatComponent::AddOrSubHealthPointRecoveryRate(float Value)
{
	HealthPointRecoveryRate += Value;

	if(OnHealthPointRecoveryRateChanged.IsBound())
	{
		OnHealthPointRecoveryRateChanged.Broadcast(HealthPointRecoveryRate);
	}
}

void UHeroStatComponent::AddOrSubMaxManaPoint(float Value)
{
	MaxManaPoint += Value;

	if(OnMaxManaPointChanged.IsBound())
	{
		OnMaxManaPointChanged.Broadcast(MaxManaPoint);
	}
}

void UHeroStatComponent::AddOrSubCurrentManaPoint(float Value)
{
	CurrentManaPoint = CurrentManaPoint + Value > MaxManaPoint ? MaxManaPoint : CurrentManaPoint + Value;
	OnCurrentManaPointChanged.Broadcast(CurrentManaPoint);
}

void UHeroStatComponent::AddOrSubManaPointRecoveryRate(float Value)
{
	ManaPointRecoveryRate += Value;

	if(OnManaPointRecoveryRateChanged.IsBound())
	{
		OnManaPointRecoveryRateChanged.Broadcast(ManaPointRecoveryRate);
	}
}

void UHeroStatComponent::AddOrSubCriticalHitProbability(float Value)
{
	CriticalHitProbability += Value;

	if(OnCriticalHitProbabilityChanged.IsBound())
	{
		OnCriticalHitProbabilityChanged.Broadcast(CriticalHitProbability);
	}
}

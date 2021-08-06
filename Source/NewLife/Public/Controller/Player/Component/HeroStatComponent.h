// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EPrimaryStat.h"
#include "ESecondaryStat.h"
#include "HeroStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInt32StatChangedSignature, int32, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatStatChangedSignature, float, Value);

class UDataTable;
class UEquipmentData;
class UWeaponData;
class UShieldData;

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Equip,
	UnEquip
};

#define MAX_LEVEL (10)
#define DEFAULT_AVAILABLE_STAT_POINT_INCREMENT (5)
#define INITIAL_STRENGTH (15)
#define INITIAL_DEXTERITY (10)
#define INITIAL_VITALITY (10)
#define INITIAL_INTELLIGENCE (5)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UHeroStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnInt32StatChangedSignature OnLevelChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnExperiencePointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnMaxExperiencePointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnInt32StatChangedSignature OnAvailableStatPointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnInt32StatChangedSignature OnStrengthChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnInt32StatChangedSignature OnDexterityChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnInt32StatChangedSignature OnVitalityChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnInt32StatChangedSignature OnIntelligenceChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnDefensePowerChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnMinDamageChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnMaxDamageChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnMaxHealthPointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnCurrentHealthPointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnHealthPointRecoveryRateChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnMaxManaPointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnCurrentManaPointChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnManaPointRecoveryRateChanged;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FOnFloatStatChangedSignature OnCriticalHitProbabilityChanged;

private:
	UPROPERTY()
	UDataTable* ExperienceDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ExperiencePoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float MaxExperiencePoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 AvailableStatPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 Strength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 Dexterity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 Vitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 Intelligence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float DefensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float MinDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float MaxDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float MaxHealthPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CurrentHealthPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float HealthPointRecoveryRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float MaxManaPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CurrentManaPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ManaPointRecoveryRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float CriticalHitProbability;

public:
	UHeroStatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void IncreaseExperiencePoint(float Value);
	void UseAvailableStatPoint(EPrimaryStat PrimaryStatType);

	void ApplyEquipEffect(EEquipType EquipType, UEquipmentData* EquipmentData);
	void ApplyWeaponDamage(EEquipType EquipType, UWeaponData* WeaponData);
	void ApplyShieldArmor(EEquipType EquipType, UShieldData* ShieldData);

	void RecoverHealth(float Value);
	void GetDamage(float Value);

	void RecoverMana(float Value);
	void UseMana(float Value);

	int32 GetPrimaryStat(EPrimaryStat PrimaryStatType);
	float GetSecondaryStat(ESecondaryStat SecondaryStatType);


protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void IncreaseLevel();
	void IncreaseAvailableStatPoint(int32 Value);
	void InitializeExperiencePoint(int32 NewLevel);
	void AddOrSubStatByType(EPrimaryStat PrimaryStatType, int32 Value);

	void AddOrSubStrength(int32 Value);
	void AddOrSubDexterity(int32 Value);
	void AddOrSubVitality(int32 Value);
	void AddOrSubIntelligence(int32 Value);

	void AddOrSubDefensePower(float Value);
	void AddOrSubMinDamage(float Value);
	void AddOrSubMaxDamage(float Value);
	void AddOrSubMaxHealthPoint(float Value);
	void AddOrSubCurrentHealthPoint(float Value);
	void AddOrSubHealthPointRecoveryRate(float Value);
	void AddOrSubMaxManaPoint(float Value);
	void AddOrSubCurrentManaPoint(float Value);
	void AddOrSubManaPointRecoveryRate(float Value);
	void AddOrSubCriticalHitProbability(float Value);

public:
	FORCEINLINE int32 GetLevel() const { return Level; }
	FORCEINLINE float GetExperiencePoint() const { return ExperiencePoint; }
	FORCEINLINE float GetMaxExperiencePoint() const { return MaxExperiencePoint; }
	FORCEINLINE int32 GetAvailableStatPoint() const { return AvailableStatPoint; }
	FORCEINLINE float GetCurrentHealthPoint() const { return CurrentHealthPoint; }
	FORCEINLINE float GetCurrentManaPoint() const { return CurrentManaPoint; }
};

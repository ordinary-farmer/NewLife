// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Common/Int32Stat.h"
#include "Common/FloatStat.h"
#include "EEquipmentSlot.h"
#include "PlayerInfoComponent.generated.h"

class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UPlayerInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FInt32Stat Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FInt32Stat AvailableStatPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat Strength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat Dexterity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat Vitality;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat DefensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat Intelligence;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat MinDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat MaxDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat AttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat HealthPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat HealthPointRecoveryRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat ManaPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat ManaPointRecoveryRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	FFloatStat ExperiencePoint;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Equipments", meta=(AllowPrivateAccess="true"))
	TMap<EEquipmentSlot, UItem*> Equipments;


public:
	// Sets default values for this component's properties
	UPlayerInfoComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FORCEINLINE TMap<EEquipmentSlot, UItem*>& GetEquipments() { return Equipments; }
};

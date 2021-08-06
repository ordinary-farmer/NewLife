// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Controller/Player/Component/PlayerInfoComponent.h"
#include "Item/DataAsset/ItemData.h"

// Sets default values for this component's properties
UPlayerInfoComponent::UPlayerInfoComponent()
	: Level(1, 20)
	  , AvailableStatPoint(0, 100)
	  , Strength(20.f, 255.f)
	  , Dexterity(10.f, 255.f)
	  , Vitality(10.f, 255.f)
	  , DefensePower(5.f, 255.f)
	  , Intelligence(5.f, 255.f)
	  , MinDamage(0.f, 255.f)
	  , MaxDamage(0.f, 255.f)
	  , AttackSpeed(1.f, 255.f)
	  , HealthPoint(Vitality.GetCurrent() * 1.5f, Vitality.GetCurrent() * 1.5f)
	  , HealthPointRecoveryRate(Vitality.GetCurrent() * 2.f, 1024.f)
	  , ManaPoint(Intelligence.GetCurrent() * 1.5f, Intelligence.GetCurrent() * 1.5f)
	  , ManaPointRecoveryRate(Intelligence.GetCurrent() * 2.f, 1024.f)
	  , ExperiencePoint(100.f, 200.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	for(int i = 0; i < static_cast<int32>(EEquipmentSlot::MaxCount); ++i)
	{
		Equipments.Emplace(static_cast<EEquipmentSlot>(i), nullptr);
	}
}


// Called when the game starts
void UPlayerInfoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

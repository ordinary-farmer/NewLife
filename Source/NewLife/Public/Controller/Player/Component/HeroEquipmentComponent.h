// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EEquipmentSlot.h"
#include "HeroEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentChangedSignature, EEquipmentSlot, EquipmentSlotType);

class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UHeroEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnEquipmentChangedSignature OnEquipmentChanged;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TMap<EEquipmentSlot, UItem*> Equipments;

public:
	UHeroEquipmentComponent();

	UItem* GetEquipment(EEquipmentSlot EquipmentSlotType);

	void InsertItem(EEquipmentSlot EquipmentSlotType, UItem* Item);

	UItem* ReleaseItem(EEquipmentSlot EquipmentSlotType);

protected:
	virtual void BeginPlay() override;
};

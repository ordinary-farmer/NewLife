// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/WeaponData.h"
#include "ShieldData.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UShieldData : public UWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Armor;

	public:
	UShieldData();

	FORCEINLINE float GetArmor() const { return Armor; }

	virtual FGameplayTag GetItemTag() override;
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/DurableEquipmentData.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS(HideDropdown)
class NEWLIFE_API UWeaponData : public UDurableEquipmentData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin="1"))
	float MinDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin="1"))
	float MaxDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData", meta=(AssetBundles="SecondaryAsset"))
	TSoftObjectPtr<UStaticMesh> BodyToLoad;

public:
	UWeaponData();

private:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:
	FORCEINLINE float GetMinDamage() const { return MinDamage; }
	FORCEINLINE float GetMaxDamage() const { return MaxDamage; }
	UStaticMesh* GetLoadedBody() const;
};

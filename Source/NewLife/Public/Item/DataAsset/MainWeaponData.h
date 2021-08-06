// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/WeaponData.h"
#include "Item/DataAsset/EMainWeapon.h"
#include "MainWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UMainWeaponData : public UWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EMainWeapon MainWeaponType;

public:
	UMainWeaponData();

	FORCEINLINE EMainWeapon GetMainWeaponType() const { return MainWeaponType; }
	virtual FGameplayTag GetItemTag() override;
};

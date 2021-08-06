// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/DurableEquipmentData.h"
#include "EArmor.h"
#include "ArmorData.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UArmorData : public UDurableEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EArmor ArmorType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ArmorData", meta=(AllowPrivateAccess="true", AssetBundles="SecondaryAsset"))
	TArray<TSoftObjectPtr<USkeletalMesh>> BodyPartsToLoad;

	UPROPERTY()
	USkeletalMesh* MergedBody;

public:
	UArmorData();

	virtual FGameplayTag GetItemTag() override;

	FORCEINLINE EArmor GetArmorType() const { return ArmorType; }

	FORCEINLINE float GetArmor() const { return Armor; }
	
	USkeletalMesh* GetLoadedBody();
};

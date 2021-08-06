// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemManagerSubsystem.generated.h"

class UDataTable;
class UItemData;
class UDurableEquipmentData;
class UItem;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UItemManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* ItemColorTable;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

	FLinearColor GetItemColor(UItemData* Data);

	void CreateItemWithAsyncLoad(FPrimaryAssetId ItemAssetId, UItem** ItemAddressToInsert, UObject* Outer);

	void ForceLoadAndCreateItem(FPrimaryAssetId ItemAssetId, UItem** ItemAddressToInsert, UObject* Outer);
	
	void AsyncLoadSecondaryAssets(UItemData* ItemData);
	
private:
	void OnPrimaryItemAssetLoadCompleted(FPrimaryAssetId ItemAssetId, UItem** ItemAddressToInsert, UObject* Outer);

	UItem* CreateItem(UItemData* Data, UObject* Outer);
};

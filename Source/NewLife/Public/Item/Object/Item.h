// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Item.generated.h"

class UItemData;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UItem : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UItemData* ItemData;

	int32 Amount;

	bool bHasDurability;

	float Durability;

public:
	UItem();

	virtual void InitializeItem(UItemData* NewData);

	void Use();
	
	int32 IncreaseAmountAndGetRemainder(int32 AmountToAdd);

	void DecreaseAmount(int32 AmountToSub);

	void DecreaseDurability(float ValueToSub);

	void RecoverDurability();

	FORCEINLINE UItemData* GetItemData() const { return ItemData; }

	FORCEINLINE int32 GetAmount() const { return Amount; }

	FORCEINLINE float GetDurability() const { return Durability; }
};

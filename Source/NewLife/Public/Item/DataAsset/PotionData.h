// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Item/DataAsset/ItemData.h"
#include "PotionData.generated.h"

UCLASS()
class NEWLIFE_API UPotionData : public UItemData
{
	GENERATED_BODY()
	
public:
	UPotionData();

	virtual FGameplayTag GetItemTag() override;
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Controller/Player/Component/EItemChangeEvent.h"
#include "Interface/InventoryInterface.h"
#include "InventoryComponent.generated.h"

class UItem;
class UEquipment;
class UPotion;
class UUWInventoryBag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemChangedSignature, int32, SlotIndex, EItemChangeEvent, ItemChangeEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UInventoryComponent : public UActorComponent, public IInventoryInterface
{
	GENERATED_BODY()

public:
	FOnItemChangedSignature OnItemChangedDelegate;
	
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<UItem*> Items;

	UPROPERTY()
	UUWInventoryBag* InventoryBagWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 RowNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 ColumnNum;

	int32 EmptyRoomCount;

public:
	UInventoryComponent();

	virtual int32 GetRowNum() override;

	virtual int32 GetColumnNum() override;

	virtual UItem* ReleaseItem(int32 Index) override;

	virtual UItem* GetItem(int32 Index) override;

	virtual void InsertItem(int32 Index, UItem* Item) override;

	virtual void PopulateTheSameItem(UItem* Item) override;

	virtual void InsertItemAtEmptyRoom(UItem* Item) override;
	
	// virtual bool TryInsertItemAutomatically(UItem* Item) override;

	virtual int32 GetEmptyRoomCount() const override;

	int32 GetEmptyRoomIndex();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	FORCEINLINE void SetInventoryBagWidget(UUWInventoryBag* NewInventoryBagWidget) { InventoryBagWidget = NewInventoryBagWidget; }
};

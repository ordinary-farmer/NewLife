// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

#define NO_EMPTY_ROOM (-1)

class UItem;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWLIFE_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetRowNum() = 0;

	virtual int32 GetColumnNum() = 0;

	virtual UItem* ReleaseItem(int32 Index) = 0;
	
	virtual UItem* GetItem(int32 Index) = 0;

	virtual void InsertItem(int32 Index, UItem* Item) = 0;

	virtual void PopulateTheSameItem(UItem* Item) = 0;

	virtual void InsertItemAtEmptyRoom(UItem* Item) = 0;
	
	virtual int32 GetEmptyRoomCount() const = 0;
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MouseInfoComponent.generated.h"

#define NO_CARRYING_ITEM (-1)

class UUWMouseCursor;
class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UMouseInfoComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cursor", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUWMouseCursor> DefaultCursorClass;

	UPROPERTY(BlueprintReadOnly, Category="Cursor", meta=(AllowPrivateAccess="true"))
	UUWMouseCursor* DefaultCursor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cursor", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUWMouseCursor> ItemCursorClass;

	UPROPERTY(BlueprintReadOnly, Category="Cursor", meta=(AllowPrivateAccess="true"))
	UUWMouseCursor* ItemCursor;

	UPROPERTY()
	UItem* CarryingItem;

	int32 CarryingItemIndex;

public:
	UMouseInfoComponent();

	UItem* ReleaseCarryingItem();

	void ReceiveCarryingItem(int32 Index, UItem* Item);

	void ReceiveCarryingItem(UItem* Item);

protected:
	virtual void BeginPlay() override;

private:
	void SwitchCursorToDefault();

	void SwitchCursorToItem(UTexture2D* NewItemTexture);

public:
	FORCEINLINE bool GetIsCarryingItem() const { return CarryingItem != nullptr;}
	
	FORCEINLINE UItem* GetCarryingItem() const { return CarryingItem; }
};

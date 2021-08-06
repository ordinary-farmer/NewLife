// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWGameHUD.generated.h"

class UCanvasPanel;
class UUWInventory;
class UUWCompassBar;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWGameHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* BasePanel;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUWCompassBar* CompassBarWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UUWInventory* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESlateVisibility InventoryWidgetVisibility;
	
public:
	UUWGameHUD(const FObjectInitializer& ObjectInitializer);

	void ToggleInventoryWidget();
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeConstruct() override;

	public:
	UUWInventory* GetInventoryWidget() const { return InventoryWidget; }
};

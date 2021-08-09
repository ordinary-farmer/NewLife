// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWGameplayMessageHandler.generated.h"

class UTextBlock;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWGameplayMessageHandler : public UUserWidget
{
	GENERATED_BODY()
		
	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* MessageTextBlock;

	UPROPERTY(Transient, meta=(AllowPrivateAccess="true", BindWidgetAnim))
	UWidgetAnimation* HideMessageAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FSlateColor TextColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FSlateColor InitialTextColor;
	
	FTimerHandle MessageTimerHandle;

public:
	void DisplayMessage(FText Message);

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

private:
	void HideMessage();
};

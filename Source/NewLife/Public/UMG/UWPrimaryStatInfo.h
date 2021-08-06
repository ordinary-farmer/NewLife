// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controller/Player/Component/EPrimaryStat.h"
#include "UWPrimaryStatInfo.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWPrimaryStatInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UButton* StatButton;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* StatName;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* StatNumber;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText StatNameText;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EPrimaryStat PrimaryStatType;

	FNumberFormattingOptions NumberFormattingOptions;
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStatChanged(int32 Value);

	UFUNCTION()
	void OnButtonClicked();
	
	UFUNCTION()
	void OnAvailableStatChanged(int32 Value);
};

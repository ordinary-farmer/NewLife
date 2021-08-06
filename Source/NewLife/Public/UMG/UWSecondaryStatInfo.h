// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controller/Player/Component/ESecondaryStat.h"
#include "UWSecondaryStatInfo.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWSecondaryStatInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* StatName;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* StatNumber;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText StatNameText;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 MaximumFractionalDigits;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	ESecondaryStat SecondaryStatType;
	
	FNumberFormattingOptions FloatNumberFormattingOptions;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnStatChanged(float Value);
};

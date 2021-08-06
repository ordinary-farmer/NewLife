// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWBasicStatInfo.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWBasicStatInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* LevelNumber;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* ExperienceNumber;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* MaxExperienceNumber;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* AvailableStatPointNumber;

	FNumberFormattingOptions FloatNumberFormattingOptions;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnLevelChanged(int32 Value);

	UFUNCTION()
	void OnExperienceChanged(float Value);

	UFUNCTION()
	void OnMaxExperienceChanged(float Value);

	UFUNCTION()
	void OnAvailableStatPointChanged(int32 Value);
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWManaBar.generated.h"

class UProgressBar;
class UTextBlock;
class UHeroStatComponent;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWManaBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UHeroStatComponent* HeroStatComp;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* CurrentManaPoint;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* MaxManaPoint;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnCurrentManaPointChanged(float Value);

	UFUNCTION()
	void OnMaxManaPointChanged(float Value);
};

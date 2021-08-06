// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWHealthBar.generated.h"

class UProgressBar;
class UTextBlock;
class UHeroStatComponent;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWHealthBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UHeroStatComponent* HeroStatComp;
	
	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* CurrentHealthPoint;

	UPROPERTY(meta=(AllowPrivateAccess="true", BindWidget))
	UTextBlock* MaxHealthPoint;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnCurrentHealthPointChanged(float Value);

	UFUNCTION()
	void OnMaxHealthPointChanged(float Value);
};

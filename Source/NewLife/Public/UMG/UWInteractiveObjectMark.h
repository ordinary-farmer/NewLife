// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInteractiveObjectMark.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWInteractiveObjectMark : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* Dot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* CircleDot;

	UPROPERTY()
	UImage* Mark;

public:
	void SetMarkDot();
	void SetMarkCircleDot();

protected:
	virtual void NativeConstruct() override;
};

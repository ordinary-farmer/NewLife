// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWMouseCursor.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UUWMouseCursor : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true", BindWidget))
	UImage* CursorImage;

public:
	void SetCursorImage(UTexture2D* CursorTexture);
};

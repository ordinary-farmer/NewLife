// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NEWLIFE_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="IInteractable")
    void OnInteract(APawn* PlayerPawn);
	
	virtual void Activate() = 0;

	virtual void Deactivate() = 0;	
	
	virtual bool TryGetScreenLocation(FVector2D& OutLocation) = 0;
	
	virtual void ToggleInteractiveWidget(bool bIsTop) = 0;

	virtual void SetInteractText(FText NewInteractText) = 0;
	
	virtual FText GetInteractText() = 0;

	virtual bool GetIsActive() = 0;
};

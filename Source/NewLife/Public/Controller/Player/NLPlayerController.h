// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NLPlayerController.generated.h"

class UUWGameHUD;
class UPlayerInfoComponent;
class UInventoryComponent;
class UMouseInfoComponent;
class UHeroStatComponent;
class UHeroEquipmentComponent;

UCLASS()
class NEWLIFE_API ANLPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HUD", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UUWGameHUD> GameHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HUD", meta=(AllowPrivateAccess="true"))
	UUWGameHUD* HUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UHeroStatComponent* HeroStatComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UHeroEquipmentComponent* HeroEquipmentComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UInventoryComponent* InventoryComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UMouseInfoComponent* MouseInfoComp;
	
public:
	ANLPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ToggleInventory();

public:
	FORCEINLINE UHeroStatComponent* GetHeroStatComp() const { return HeroStatComp; }
	FORCEINLINE UHeroEquipmentComponent* GetHeroEquipmentComp() const { return HeroEquipmentComp; }
	FORCEINLINE UInventoryComponent* GetInventoryComp() const { return InventoryComp; }
	FORCEINLINE UMouseInfoComponent* GetMouseInfoComp() const { return MouseInfoComp; }

	UFUNCTION(BlueprintCallable)
	UUWGameHUD* GetGameHUD() const;
};

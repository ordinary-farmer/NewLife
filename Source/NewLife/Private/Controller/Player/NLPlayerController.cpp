// Fill out your copyright notice in the Description page of Project Settings.

#include "Controller/Player/NLPlayerController.h"
#include "UMG/UWGameHUD.h"
#include "Controller/Player/Component/InventoryComponent.h"
#include "Controller/Player/Component/MouseInfoComponent.h"
#include "Controller/Player/Component/HeroStatComponent.h"
#include "Controller/Player/Component/HeroEquipmentComponent.h"

ANLPlayerController::ANLPlayerController()
{
	HeroStatComp = CreateDefaultSubobject<UHeroStatComponent>(TEXT("HeroStatComp"));
	HeroEquipmentComp = CreateDefaultSubobject<UHeroEquipmentComponent>(TEXT("HeroEquipmentComp"));
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
	MouseInfoComp = CreateDefaultSubobject<UMouseInfoComponent>(TEXT("MouseInfoComp"));
}

void ANLPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	HUD = CreateWidget<UUWGameHUD>(this, GameHUDClass);
	HUD->AddToViewport();
}

void ANLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &ANLPlayerController::ToggleInventory);
}

void ANLPlayerController::ToggleInventory()
{
	HUD->ToggleInventoryWidget();
}

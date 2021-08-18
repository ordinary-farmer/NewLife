// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Placeable/InteractiveActors/ItemContainer.h"
#include "Controller/Player/NLPlayerController.h"
#include "Interface/InventoryInterface.h"
#include "Item/Object/Item.h"
#include "Kismet/GameplayStatics.h"
#include "Singleton/ItemManagerSubsystem.h"
#include "Singleton/GameplayMessageHandlerSubsystem.h"
#include "Controller/Player/Component/InventoryComponent.h"

AItemContainer::AItemContainer()
{
	ItemAssetIds.Init(FPrimaryAssetId(), 4);
	Items.Init(nullptr, 4);
}

void AItemContainer::OnInteract_Implementation(APawn* PlayerPawn)
{
	Super::OnInteract_Implementation(PlayerPawn);
	
	ANLPlayerController* PlayerController = Cast<ANLPlayerController>(PlayerPawn->GetController());
	check(PlayerController);

	IInventoryInterface* Inventory = Cast<IInventoryInterface>(PlayerController->GetInventoryComp());
	check(Inventory);

	UGameInstance* GameInstance = GetGameInstance();
	check(GameInstance);
	
	UItemManagerSubsystem* ItemManager = GameInstance->GetSubsystem<UItemManagerSubsystem>();
	check(ItemManager);

	bool bIsInventoryFull = false;
	
	for (int32 i = ItemAssetIds.Num() - 1; i >= 0; --i)
	{
		if (ItemAssetIds[i].IsValid())
		{
			if(Items[i] == nullptr)
			{
				ItemManager->ForceLoadAndCreateItem(ItemAssetIds[i], &Items[i], this);
				check(Items[i]);				
			}

			Inventory->PopulateTheSameItem(Items[i]);

			if(Items[i]->GetAmount() == 0)
			{
				Items[i]->ConditionalBeginDestroy();
				Items[i] = nullptr;
			}
			else
			{
				if(Inventory->GetEmptyRoomCount() > 0)
				{
					Inventory->InsertItemAtEmptyRoom(Items[i]);
					Items[i] = nullptr;
				}
			}

			if(Items[i] == nullptr)
			{
				ItemAssetIds.RemoveAt(i);
				Items.RemoveAt(i);
			}
			else
			{
				bIsInventoryFull = true;
				break;
			}
		}
	}

	if(bIsInventoryFull)
	{
		// 인벤토리가 가득찼다는 경고를 띄워야 함!
		UGameplayMessageHandlerSubsystem* GameplayMessageHandler = GameInstance->GetSubsystem<UGameplayMessageHandlerSubsystem>();

		GameplayMessageHandler->DisplayMessage(FString("BagFull"));
		Activate();
	}
}

void AItemContainer::OnRecognitionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnRecognitionSphereOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UGameInstance* GameInstance = GetGameInstance();
	check(GameInstance);
	
	UItemManagerSubsystem* ItemManager = GameInstance->GetSubsystem<UItemManagerSubsystem>();
	check(ItemManager);

	for(int32 i = 0; i < ItemAssetIds.Num(); ++i)
	{
		if(ItemAssetIds[i].IsValid())
		{
			ItemManager->CreateItemWithAsyncLoad(ItemAssetIds[i], &Items[i], this);
		}
	}
}

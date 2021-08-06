// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Placeable/InteractiveActors/BaseInteractive.h"
#include "ItemContainer.generated.h"

class UItem;

UCLASS()
class NEWLIFE_API AItemContainer : public ABaseInteractive
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Item", EditFixedSize, meta=(AllowPrivateAccess="true"))
	TArray<FPrimaryAssetId> ItemAssetIds;

	UPROPERTY()
	TArray<UItem*> Items;
	
public:
	AItemContainer();

	/* 가지고 있는 아이템들을 인벤토리에 넣습니다. 아이템 데이터 애셋은 존재하나 아이템이 생성되지 않은 경우 동기 로드해서 아이템을 생성합니다. */
	virtual void OnInteract_Implementation(APawn* PlayerPawn) override;

	/* 플레이어가 아이템 컨테이너를 인식하면 가지고 있는 아이템 데이터 애셋들로 아이템을 생성합니다. */
	virtual void OnRecognitionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult) override;
};

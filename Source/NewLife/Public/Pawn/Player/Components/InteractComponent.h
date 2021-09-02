// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/Interactable.h"
#include "InteractComponent.generated.h"

USTRUCT()
struct FTopInteractive
{
	GENERATED_BODY()

	FTopInteractive()
		: Interactive(nullptr)
		  , Key("None")
	{
	}

	bool operator==(const FTopInteractive& Rhs) const
	{
		return Key == Rhs.Key;
	}

	bool operator!=(const FTopInteractive& Rhs) const
	{
		return Key != Rhs.Key;
	}

	FTopInteractive& operator=(const FTopInteractive& Rhs)
	{
		if (this == &Rhs)
		{
			return *this;
		}

		Interactive = Rhs.Interactive;
		Key = Rhs.Key;

		return *this;
	}

	IInteractable* Interactive;

	FString Key;
};

class UInteractHelperWidgetComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY()
	APawn* OwnerPawn;
	
	UPROPERTY()
	UInteractHelperWidgetComponent* OwnerInteractHelperWidget;
	
	// 스크린 중앙 좌표
	FVector2D ScreenCenterCoord;

	// Pawn이 인식한 IInteractable들의 Map, Key는 Actor의 GetName()의 반환값
	TMap<FString, IInteractable*> RecognizedObjects;

	// Pawn이 상호작용가능한 IInteractable들의 Map, Key는 Actor의 GetName()의 반환값
	TMap<FString, IInteractable*> InteractableObjects;

	// 상호작용 최우선순위 IInteractable
	FTopInteractive TopInteractive;

public:
	// Sets default values for this component's properties
	UInteractComponent();

	/** TopInteractive와 상호작용 */
	UFUNCTION(BlueprintCallable)
	void Interact();

	/** RecognizedActor에 새로운 IInteractable을 추가 */
	void PushRecognized(AActor* Actor);

	/** RecognizedActor에 IInteractable을 제거 */
	void PopRecognized(AActor* Actor);

	bool IsRecognizedContains(AActor* Actor) const;

	void PushInteractable(AActor* Actor);

	void PopInteractable(AActor* Actor);

	bool IsInteractableContains(AActor* Actor) const;

protected:	
	virtual void InitializeComponent() override;
	
	/** TopInteractive를 갱신 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	/** 상호작용 가능한 IInteractable 중 최우선 Interactable를 갱신 */
	void UpdateTopInteractableActor();

	void SetScreenCenterCoord(FViewport* Viewport, uint32 Value);

	FORCEINLINE void InitializeTopInteractive()
	{
		TopInteractive.Interactive = nullptr;
		TopInteractive.Key = FString("None");
	}

public:
	FORCEINLINE int32 GetInteractableObjectsNum() const { return InteractableObjects.Num(); }

	FORCEINLINE void SetTopInteractive(IInteractable* NewTopInteractable, FString NewTopKey)
	{
		TopInteractive.Interactive = NewTopInteractable;
		TopInteractive.Key = NewTopKey;
	}
};

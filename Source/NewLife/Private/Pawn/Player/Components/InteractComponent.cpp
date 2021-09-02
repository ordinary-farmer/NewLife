// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/Components/InteractComponent.h"
#include "Pawn/Player/Components/InteractHelperWidgetComponent.h"
#include "Kismet/GameplayStatics.h"

#include "UMG/UWInteractHelper.h"

UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UInteractComponent::InitializeComponent()
{
	OwnerPawn = Cast<APawn>(GetOwner());

	check(OwnerPawn);

	OwnerInteractHelperWidget = Cast<UInteractHelperWidgetComponent>(OwnerPawn->GetComponentByClass(UInteractHelperWidgetComponent::StaticClass()));

	check(OwnerInteractHelperWidget);
}

void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TopInteractive.Interactive != nullptr && OwnerInteractHelperWidget->GetVisibleFlag() == false)
	{
		OwnerInteractHelperWidget->SetVisibility(true);
	}
	else if (TopInteractive.Interactive == nullptr && OwnerInteractHelperWidget->GetVisibleFlag() == true)
	{
		OwnerInteractHelperWidget->SetVisibility(false);
	}

	UpdateTopInteractableActor();
}

void UInteractComponent::Interact()
{
	if(TopInteractive.Interactive == nullptr)
	{
		return;
	}	
	
	TopInteractive.Interactive->Execute_OnInteract(Cast<UObject>(TopInteractive.Interactive), OwnerPawn);
	TopInteractive.Interactive->Deactivate();
}

void UInteractComponent::PushRecognized(AActor* Actor)
{
	if(Actor == nullptr)
	{
		return;
	}

	IInteractable* InteractableActorTemp = Cast<IInteractable>(Actor);
	
	if(InteractableActorTemp)
	{
		const FString ActorName(Actor->GetName());

		RecognizedObjects.Add(ActorName, InteractableActorTemp);
	}
}

void UInteractComponent::PopRecognized(AActor* Actor)
{
	if(Actor == nullptr)
	{
		return;
	}

	RecognizedObjects.Remove(Actor->GetName());
}

bool UInteractComponent::IsRecognizedContains(AActor* Actor) const
{
	return RecognizedObjects.Contains(Actor->GetName());
}

void UInteractComponent::PushInteractable(AActor* Actor)
{
	if(Actor == nullptr)
	{
		return;
	}

	IInteractable* InteractableActorTemp = Cast<IInteractable>(Actor);
	
	if(InteractableActorTemp)
	{
		const FString ActorName(Actor->GetName());

		InteractableObjects.Add(ActorName, InteractableActorTemp);
	}	
}

void UInteractComponent::PopInteractable(AActor* Actor)
{
	if(Actor == nullptr)
	{
		return;
	}

	IInteractable* InteractableActorTemp = Cast<IInteractable>(Actor);

	if(InteractableActorTemp)
	{
		InteractableActorTemp->ToggleInteractiveWidget(false);
		
		InteractableObjects.Remove(Actor->GetName());

		if(InteractableObjects.Num() == 0)
		{
			InitializeTopInteractive();
		}
	}
}

bool UInteractComponent::IsInteractableContains(AActor* Actor) const
{
	return InteractableObjects.Contains(Actor->GetName());
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &UInteractComponent::SetScreenCenterCoord);

	SetScreenCenterCoord(GEngine->GameViewport->Viewport, 0);
}

void UInteractComponent::UpdateTopInteractableActor()
{
	if(InteractableObjects.Num() == 0)
	{
		return;
	}

	float MinDistance = TNumericLimits<float>::Max();

	FTopInteractive Tmp;

	for (auto& Elem : InteractableObjects)
	{
		if(Elem.Value->GetIsActive() == false)
		{
			continue;
		}
		
		FVector2D ElemScreenLocation;
		if (Elem.Value->TryGetScreenLocation(ElemScreenLocation))
		{
			const float DistanceBetween = FVector2D::Distance(ScreenCenterCoord, ElemScreenLocation);
			if (MinDistance > DistanceBetween)
			{
				MinDistance = DistanceBetween;
				Tmp.Interactive = Cast<IInteractable>(Elem.Value);
				Tmp.Key = Elem.Key;
			}
		}
	}
	
	if(TopInteractive.Interactive != nullptr)
	{
		TopInteractive.Interactive->ToggleInteractiveWidget(false);
	}
	
	if(Tmp.Interactive != nullptr)
	{
		Tmp.Interactive->ToggleInteractiveWidget(true);
		OwnerInteractHelperWidget->UpdateText(Tmp.Interactive->GetInteractText());
	}
	
	TopInteractive = Tmp;
	
	// if(Tmp != TopInteractive)
	// {
		// if(TopInteractive.Interactive != nullptr)
		// {
		// 	TopInteractive.Interactive->ToggleInteractiveWidget(false);
		// }
		//
		// if(Tmp.Interactive != nullptr)
		// {
		// 	Tmp.Interactive->ToggleInteractiveWidget(true);
		// 	OwnerInteractHelperWidget->UpdateText(Tmp.Interactive->GetInteractText());
		// }
		//
		// TopInteractive = Tmp;
	// }
}

void UInteractComponent::SetScreenCenterCoord(FViewport* Viewport, uint32 Value)
{
	if(Viewport == nullptr)
	{
		return;
	}
	
	FVector2D ViewPortSize;

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	ScreenCenterCoord = ViewPortSize / 2;
}





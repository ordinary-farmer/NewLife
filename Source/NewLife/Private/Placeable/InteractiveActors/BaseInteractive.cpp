// Fill out your copyright notice in the Description page of Project Settings.


#include "Placeable/InteractiveActors/BaseInteractive.h"
#include "Placeable/InteractiveActors/InteractAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/Player/Components/InteractComponent.h"
#include "UMG/UWInteractiveObjectMark.h"

// Sets default values
ABaseInteractive::ABaseInteractive()
	: bAutoInteractionSphereRadius(true)
    , bIsActive(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetCollisionProfileName("Interactive");
	SetRootComponent(InteractionSphere);

	RecognitionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RecognitionSphere"));
	RecognitionSphere->SetCollisionProfileName("Interactive");
	RecognitionSphere->SetupAttachment(RootComponent);

	MarkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MarkWidget"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(
        TEXT("WidgetBlueprint'/Game/_NewLife/UI/WB_InteractiveObjectMark.WB_InteractiveObjectMark_C'"));
	if (WidgetAsset.Succeeded())
	{
		MarkWidget->SetWidgetClass(WidgetAsset.Class);
	}
	MarkWidget->SetWidgetSpace(EWidgetSpace::Screen);
	MarkWidget->SetupAttachment(RootComponent);	
	MarkWidget->SetDrawSize(FVector2D(16.f, 16.f));
	MarkWidget->SetVisibility(false);

	Attribute = CreateDefaultSubobject<UInteractAttributeComponent>(TEXT("Attribute"));
}

void ABaseInteractive::OnConstruction(const FTransform& Transform)
{
	FVector MyOrigin = RootComponent->GetComponentLocation();

	const float OriginZLocation = MyOrigin.Z;
	float MarkWidgetZLocation = 0;

	FVector OriginXY = MyOrigin;
	OriginXY.Z = 0.f;
	float InteractionSphereRadius = DEFAULT_INTERACTION_SPHERE_RADIUS;

	TArray<USceneComponent*> Components;
	RootComponent->GetChildrenComponents(true, Components);

	for (auto& Elem : Components)
	{
		UPrimitiveComponent* CollisionComponent = Cast<UPrimitiveComponent>(Elem);
		if (CollisionComponent && (CollisionComponent->GetCollisionEnabled() == ECollisionEnabled::Type::PhysicsOnly ||
			CollisionComponent->GetCollisionEnabled() == ECollisionEnabled::Type::QueryAndPhysics))
		{
			FVector ComponentLocation = CollisionComponent->GetComponentLocation();
			FVector ComponentBoxExtent = CollisionComponent->Bounds.BoxExtent;

			const float TmpZ = ComponentLocation.Z - OriginZLocation + ComponentBoxExtent.Z;
			if (TmpZ > MarkWidgetZLocation)
			{
				MarkWidgetZLocation = TmpZ;
			}

			if (bAutoInteractionSphereRadius == false)
			{
				continue;
			}

			if (ComponentLocation.X - OriginXY.X < 0.f)
			{
				ComponentBoxExtent.X *= -1.f;
			}

			if (ComponentLocation.Y - OriginXY.Y < 0.f)
			{
				ComponentBoxExtent.Y *= -1.f;
			}

			FVector Point1 = FVector(ComponentLocation.X + ComponentBoxExtent.X, ComponentLocation.Y, 0.f);
			FVector Point2 = FVector(ComponentLocation.X, ComponentLocation.Y + ComponentBoxExtent.Y, 0.f);
			FVector Point3 = FVector(ComponentLocation.X + ComponentBoxExtent.X,
			                         ComponentLocation.Y + ComponentBoxExtent.Y, 0.f);

			const float Distance1 = FVector::Distance(OriginXY, Point1);
			const float Distance2 = FVector::Distance(OriginXY, Point2);
			const float Distance3 = FVector::Distance(OriginXY, Point3);

			const float TmpRadius = FMath::Max3(Distance1, Distance2, Distance3);
			if (TmpRadius > InteractionSphereRadius)
			{
				InteractionSphereRadius = TmpRadius;
			}
		}
	}

	InteractionSphere->SetSphereRadius(InteractionSphereRadius + INTERACTABLE_RANGE);
	RecognitionSphere->SetSphereRadius(RECOGNITION_RANGE);

	MarkWidgetZLocation = FMath::Clamp(MarkWidgetZLocation, 0.f, MAX_REACT_MARK_Z_LOCATION);
	MarkWidget->SetRelativeLocation(FVector(0.f, 0.f, MarkWidgetZLocation));
}

void ABaseInteractive::OnInteract_Implementation(APawn* PlayerPawn)
{
	Attribute->GenerateInteractionEffects(PlayerPawn);
}

void ABaseInteractive::Activate()
{
	bIsActive = true;

	TArray<AActor*> OverlappingActors;
	
	RecognitionSphere->GetOverlappingActors(OverlappingActors);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AActor* PlayerPawn = PlayerController->GetPawn();

	bool bFoundPawnInOverlappingActors = false;
	
	for(auto* Actor : OverlappingActors)
	{
		if(PlayerPawn == Actor)
		{
			bFoundPawnInOverlappingActors = true;
			break;
		}
	}

	if(bFoundPawnInOverlappingActors)
	{
		UInteractComponent* InteractionSubjectComp = Cast<UInteractComponent>(PlayerPawn->GetComponentByClass(UInteractComponent::StaticClass()));
		
		if(InteractionSubjectComp)
		{
			MarkWidget->SetVisibility(true);
		}
	}
}

void ABaseInteractive::Deactivate()
{
	bIsActive = false;
	MarkWidget->SetVisibility(false);
	ToggleInteractiveWidget(false);
}

bool ABaseInteractive::GetScreenLocation(FVector2D& OutLocation)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);

	if (Controller)
	{
		//return Controller->ProjectWorldLocationToScreen(GetActorLocation(), OutLocation);
		return Controller->ProjectWorldLocationToScreen(MarkWidget->GetComponentLocation(), OutLocation);
	}

	return false;
}

void ABaseInteractive::ToggleInteractiveWidget(bool bIsTop)
{
	UUWInteractiveObjectMark* Widget = Cast<UUWInteractiveObjectMark>(MarkWidget->GetUserWidgetObject());

	check(Widget);
	
	if (bIsTop)
	{
		Widget->SetMarkCircleDot();
	}
	else
	{
		Widget->SetMarkDot();
	}
}

void ABaseInteractive::SetInteractText(FText NewInteractText)
{
	InteractText = NewInteractText;
}

FText ABaseInteractive::GetInteractText()
{
	return InteractText;
}

bool ABaseInteractive::GetIsActive()
{
	return bIsActive;
}

// Called when the game starts or when spawned
void ABaseInteractive::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractive::OnInteractionSphereOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractive::OnInteractionSphereOverlapEnd);

	RecognitionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractive::OnRecognitionSphereOverlapBegin);
	RecognitionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractive::OnRecognitionSphereOverlapEnd);
}

void ABaseInteractive::OnRecognitionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UInteractComponent* PlayerInteractComponent = Cast<UInteractComponent>(OtherActor->GetComponentByClass(UInteractComponent::StaticClass()));

	if(PlayerInteractComponent)
	{
		PlayerInteractComponent->PushRecognized(this);
		
		if(bIsActive)
		{
			MarkWidget->SetVisibility(true);
		}
	}
}

void ABaseInteractive::OnRecognitionSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UInteractComponent* PlayerInteractComponent = Cast<UInteractComponent>(OtherActor->GetComponentByClass(UInteractComponent::StaticClass()));

	if(PlayerInteractComponent)
	{
		PlayerInteractComponent->PopRecognized(this);
		
		if(bIsActive && MarkWidget->GetVisibleFlag())
		{
			MarkWidget->SetVisibility(false);
		}
	}
}

void ABaseInteractive::OnInteractionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UInteractComponent* PlayerInteractComponent = Cast<UInteractComponent>(OtherActor->GetComponentByClass(UInteractComponent::StaticClass()));

	if(PlayerInteractComponent && PlayerInteractComponent->IsRecognizedContains(this))
	{
		PlayerInteractComponent->PopRecognized(this);
		PlayerInteractComponent->PushInteractable(this);
	}
}

void ABaseInteractive::OnInteractionSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UInteractComponent* PlayerInteractComponent = Cast<UInteractComponent>(OtherActor->GetComponentByClass(UInteractComponent::StaticClass()));

	if(PlayerInteractComponent && PlayerInteractComponent->IsInteractableContains(this))
	{
		PlayerInteractComponent->PopInteractable(this);
		PlayerInteractComponent->PushRecognized(this);
	}
}

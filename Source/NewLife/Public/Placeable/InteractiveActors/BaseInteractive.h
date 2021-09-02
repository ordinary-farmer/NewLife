// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "BaseInteractive.generated.h"

#define RECOGNITION_RANGE (800.f)
#define MAX_REACT_MARK_Z_LOCATION (270.f)
#define DEFAULT_INTERACTION_SPHERE_RADIUS (32.f)
#define INTERACTABLE_RANGE (100.f)

class USphereComponent;
class UWidgetComponent;
class UInteractAttributeComponent;

UCLASS()
class NEWLIFE_API ABaseInteractive : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = true))
	USphereComponent* RecognitionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = true))
	USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = true))
	UWidgetComponent* MarkWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive", meta = (AllowPrivateAccess = true))
	UInteractAttributeComponent* Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactive", meta=(AllowPrivateAccess="true"))
	FText InteractText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interactive", meta = (AllowPrivateAccess = true))
	bool bAutoInteractionSphereRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interactive", meta=(AllowPrivateAccess="true"))
	bool bIsActive;

public:
	// Sets default values for this actor's properties
	ABaseInteractive();

	virtual void OnInteract_Implementation(APawn* PlayerPawn) override;

	UFUNCTION(BlueprintCallable, Category="IInteractable")
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category="IInteractable")
	virtual void Deactivate() override;

	virtual bool TryGetScreenLocation(FVector2D& OutLocation) override;

	virtual void ToggleInteractiveWidget(bool bIsTop) override;

	UFUNCTION(BlueprintCallable, Category="IInteractable")
	virtual void SetInteractText(FText NewInteractText) override;
	
	virtual FText GetInteractText() override;

	virtual bool GetIsActive() override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnRecognitionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                             const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnRecognitionSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnInteractionSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                             const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnInteractionSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE USphereComponent* GetRecognitionSphere() const { return RecognitionSphere; }
	FORCEINLINE USphereComponent* GetInteractionSphere() const { return InteractionSphere; }
	FORCEINLINE UWidgetComponent* GetMarkWidget() const { return MarkWidget; }
	FORCEINLINE UInteractAttributeComponent* GetAttribute() const { return Attribute; }
};

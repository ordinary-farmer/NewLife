// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "TableRowBase/CamMoveInfoRow.h"
#include "HeroSpringArmComponent.generated.h"

#define ERROR_TOLERANCE (0.01f)

UENUM(BlueprintType)
enum class ECamMoveMode : uint8
{
	None UMETA(DisplayName="None"),
	Normal UMETA(DisplayName="Normal"),
	Sprint UMETA(DisplayName="Sprint"),
	WaitInput UMETA(DisplayName="WaitInput"),
	Combat UMETA(DisplayName="Combat")
};

class UDataTable;

UCLASS()
class NEWLIFE_API UHeroSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	bool bShouldMoveCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	FCamMoveInfoRow CamMoveInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	ECamMoveMode CamMoveMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	bool bIsTargetArmLengthSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	bool bIsSocketOffsetSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	bool bIsRelativeRotationSet;

	UPROPERTY(VisibleAnywhere, Category="Camera Move Info", meta=(AllowPrivateAccess="true"))
	UDataTable* CamMoveInfoTable;

public:
	UHeroSpringArmComponent();

	void SetCamMoveMode(ECamMoveMode NewCamMoveMode);

	FORCEINLINE ECamMoveMode GetCamMoveMode() const { return CamMoveMode; }

protected:
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

private:
	void StartCameraMove();

	void MoveCamera(float DeltaTime);
};

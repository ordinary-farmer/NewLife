// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/Hero/HeroSpringArmComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Singleton/NLGameInstance.h"

UHeroSpringArmComponent::UHeroSpringArmComponent()
	: bShouldMoveCamera(false)
	  , bIsTargetArmLengthSet(false)
	  , bIsSocketOffsetSet(false)
	  , bIsRelativeRotationSet(false)
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	bUsePawnControlRotation = true; // Rotate the arm based on the controller
	bEnableCameraLag = true;
	bEnableCameraRotationLag = true;
	CameraLagSpeed = 10.f;
	CameraRotationLagSpeed = 50.f;
	CameraLagMaxDistance = 10.f;
}

void UHeroSpringArmComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UNLGameInstance* GameInstance = Cast<UNLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance == nullptr)
	{
		return;
	}

	CamMoveInfoTable = GameInstance->GetCameraMoveInfoTable();
}

void UHeroSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString CamMoveModeString;
	
	switch(CamMoveMode)
	{
		case ECamMoveMode::Normal:
			CamMoveModeString = FString("Normal");
			break;
		case ECamMoveMode::Sprint:
			CamMoveModeString = FString("Sprint");
			break;
		case ECamMoveMode::Combat:
			CamMoveModeString = FString("Combat");
			break;
		case ECamMoveMode::WaitInput:
			CamMoveModeString = FString("WaitInput");
			break;
		default:
			break;
	}

	MoveCamera(DeltaTime);
}

void UHeroSpringArmComponent::MoveCamera(float DeltaTime)
{
	if (bShouldMoveCamera == false)
	{
		return;
	}

	if (bIsTargetArmLengthSet == false)
	{
		if (FMath::IsNearlyEqual(TargetArmLength, CamMoveInfo.TargetArmLength, ERROR_TOLERANCE))
		{
			bIsTargetArmLengthSet = true;
		}
		else
		{
			TargetArmLength = FMath::FInterpTo(TargetArmLength, CamMoveInfo.TargetArmLength,
			                                   DeltaTime, CamMoveInfo.InterpSpeed_TargetArmLength);
		}
	}

	if (bIsSocketOffsetSet == false)
	{
		if (SocketOffset.Equals(CamMoveInfo.SocketOffset, ERROR_TOLERANCE))
		{
			bIsSocketOffsetSet = true;
		}
		else
		{
			SocketOffset = FMath::VInterpTo(SocketOffset, CamMoveInfo.SocketOffset, DeltaTime,
			                                CamMoveInfo.InterpSpeed_SocketOffset);
		}
	}

	if (bIsRelativeRotationSet == false)
	{
		if (GetRelativeRotation().Equals(CamMoveInfo.RelativeRotation, ERROR_TOLERANCE))
		{
			bIsRelativeRotationSet = true;
		}
		else
		{
			const FRotator NewRelativeRotation = FMath::RInterpTo(GetRelativeRotation(), CamMoveInfo.RelativeRotation,
			                                                      DeltaTime, CamMoveInfo.InterpSpeed_RelativeRotation);
			SetRelativeRotation(NewRelativeRotation);
		}
	}

	const bool bIsCameraMoveFinished = bIsTargetArmLengthSet && bIsSocketOffsetSet && bIsRelativeRotationSet;

	if (bIsCameraMoveFinished)
	{
		bShouldMoveCamera = false;
	}
}

void UHeroSpringArmComponent::SetCamMoveMode(ECamMoveMode NewCamMoveMode)
{
	check(NewCamMoveMode != ECamMoveMode::None);
	
	if(CamMoveMode == NewCamMoveMode)
	{
		return;
	}
	
	CamMoveMode = NewCamMoveMode;
	FCamMoveInfoRow* RowPtr = nullptr;
	
	switch (CamMoveMode)
	{
	case ECamMoveMode::Normal:
		RowPtr = reinterpret_cast<FCamMoveInfoRow*>(*CamMoveInfoTable->GetRowMap().Find(FName("Normal")));		
		break;
	case ECamMoveMode::Sprint:
		RowPtr = reinterpret_cast<FCamMoveInfoRow*>(*CamMoveInfoTable->GetRowMap().Find(FName("Sprint")));		
		break;
	case ECamMoveMode::Combat:
		RowPtr = reinterpret_cast<FCamMoveInfoRow*>(*CamMoveInfoTable->GetRowMap().Find(FName("Combat")));		
		break;
	case ECamMoveMode::WaitInput:
		RowPtr = reinterpret_cast<FCamMoveInfoRow*>(*CamMoveInfoTable->GetRowMap().Find(FName("WaitInput")));		
		break;
	default:
		checkNoEntry();
	}

	check(RowPtr);
	CamMoveInfo = *RowPtr;

	StartCameraMove();
}

void UHeroSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCamMoveMode(ECamMoveMode::Normal);
}

void UHeroSpringArmComponent::StartCameraMove()
{
	bShouldMoveCamera = true;
	bIsTargetArmLengthSet = false;
	bIsSocketOffsetSet = false;
	bIsRelativeRotationSet = false;
}

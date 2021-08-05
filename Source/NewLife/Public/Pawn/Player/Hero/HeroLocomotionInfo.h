// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroLocomotionInfo.generated.h"

UENUM(BlueprintType)
enum class EHeroGait : uint8
{
	Walking		UMETA(DisplayName="Walking"),
    Running		UMETA(DisplayName="Running"),
    Sprinting	UMETA(DisplayName="Sprinting")
};

USTRUCT(BlueprintType)
struct FHeroLocomotionInfo
{
	GENERATED_BODY()

	FHeroLocomotionInfo()
		: Gait(EHeroGait::Running)
        , Speed(0.f)
        , Acceleration(0.f)
        , bIsMoving(false)
        , bIsAccelerating(false)
        , bIsInAir(false)
        , bMoveInput(false)
        , bPressedJump(false)
        , bPressedSprint(false) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroGait Gait;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Acceleration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMoveInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPressedJump;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPressedSprint;
};
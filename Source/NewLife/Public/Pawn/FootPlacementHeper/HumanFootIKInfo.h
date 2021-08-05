// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HumanFootIKInfo.generated.h"

/**
 * Foot IK Info Values
 */

USTRUCT(BlueprintType)
struct FHumanFootIKInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector)
	float LeftFootOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)
	float LeftFootIKAlpha = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector)
	FRotator LeftFootAngle = FRotator(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
	float RightFootOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)
	float RightFootIKAlpha = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Angle)
	FRotator RightFootAngle = FRotator(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector)
	float ZOffset = 0.f;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CamMoveInfoRow.generated.h"

USTRUCT(BlueprintType)
struct FCamMoveInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	FCamMoveInfoRow()
        : TargetArmLength(0.f)
        , InterpSpeed_TargetArmLength(0.f)
        , SocketOffset(FVector::ZeroVector)
        , InterpSpeed_SocketOffset(0.f)	
        , RelativeRotation(FRotator::ZeroRotator)
		, InterpSpeed_RelativeRotation(0.f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InterpSpeed_TargetArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector SocketOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InterpSpeed_SocketOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InterpSpeed_RelativeRotation;
};
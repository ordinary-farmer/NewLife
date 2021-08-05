// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_SetDistance.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UCAnimNotifyState_SetDistance : public UAnimNotifyState
{
	GENERATED_BODY()

	bool bIsGameWorld;
	
	FVector ActorOriginLocation;

	FVector ActorForwardVector;

	FFloatCurve DistanceCurve;

	float ProcessingTime;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};

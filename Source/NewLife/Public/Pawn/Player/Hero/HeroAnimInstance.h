// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroLocomotionInfo.h"
#include "Pawn/FootPlacementHeper/HumanFootIKInfo.h"
#include "Pawn/FootPlacementHeper/HumanFootIKHelper.h"
#include "HeroAnimInstance.generated.h"

class AHero;

UCLASS()
class NEWLIFE_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AHero* Owner;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	EHeroGait Gait;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	float Speed;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	float Acceleration;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	bool bIsMoving;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	bool bIsAccelerating;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	bool bIsInAir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	bool bPressedJump;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	bool bPressedSprint;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	bool bShouldPlayRunEnd;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Locomotion", meta=(AllowPrivateAccess="true"))
	float RunEndPlayRate;
	
	TUniquePtr<FHumanFootIKHelper> FootIKManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="FootIK", meta=(AllowPrivateAccess="true"))
	FHumanFootIKInfo FootIKInfo;	
	
public:
	UHeroAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	void ChooseMoveEndAnimation();
	
	UFUNCTION()
	void AnimNotify_MoveStartToMoveEnd();

	UFUNCTION()
	void AnimNotify_MovingOut();

	UFUNCTION()
	void AnimNotify_MoveEndIn();

	UFUNCTION()
    void AnimNotify_MoveEndOut();

	UFUNCTION()
	void AnimNotify_LandIn();

	UFUNCTION()
    void AnimNotify_LandOut();
};

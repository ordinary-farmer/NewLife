// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/FootPlacementHeper/HumanFootIKHelper.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

const float FHumanFootIKHelper::TraceDistanceFromFoot = 50.f;

FHumanFootIKHelper::FHumanFootIKHelper()
{
}

FHumanFootIKHelper::~FHumanFootIKHelper()
{
}

FHumanFootIKInfo FHumanFootIKHelper::UpdateFootIKInfo(UWorld* World, ACharacter* Character,
	FHumanFootIKInfo CurrentFootIKInfo, float Deltatime)
{
	check(Character);

	FHumanFootIKInfo DesiredFootIKInfo;

	FVector IKFootRootLocation = Character->GetMesh()->GetSocketLocation(IK_FOOT_ROOT_SOCK_NAME);
	FVector LeftFootLocation = Character->GetMesh()->GetSocketLocation(LEFT_FOOT_SOCK_NAME);
	LeftFootLocation.Z = IKFootRootLocation.Z;
	FVector RightFootLocation = Character->GetMesh()->GetSocketLocation(RIGHT_FOOT_SOCK_NAME);
	RightFootLocation.Z = IKFootRootLocation.Z;

	FVector LeftTraceStart = FVector(LeftFootLocation.X, LeftFootLocation.Y, Character->GetActorLocation().Z);
	FVector LeftTraceEnd = FVector(LeftFootLocation.X, LeftFootLocation.Y,
	                               IKFootRootLocation.Z - TraceDistanceFromFoot);

	FVector RightTraceStart = FVector(RightFootLocation.X, RightFootLocation.Y, Character->GetActorLocation().Z);
	FVector RightTraceEnd = FVector(RightFootLocation.X, RightFootLocation.Y,
	                                IKFootRootLocation.Z - TraceDistanceFromFoot);

	FCollisionQueryParams TraceQueryParams(NAME_None, false, Character);

	FHitResult LeftHitResult;
	FHitResult RightHitResult;

	World->LineTraceSingleByChannel(
		LeftHitResult,
		LeftTraceStart,
		LeftTraceEnd,
		ECC_Camera,
		TraceQueryParams
	);

	World->LineTraceSingleByChannel(
		RightHitResult,
		RightTraceStart,
		RightTraceEnd,
		ECC_Camera,
		TraceQueryParams
	);

	if (LeftHitResult.Location.Z > RightHitResult.Location.Z)
	{
		DesiredFootIKInfo.LeftFootOffset = LeftHitResult.Location.Z - RightHitResult.Location.Z;
		if (DesiredFootIKInfo.LeftFootOffset > 41.f)
		{
			DesiredFootIKInfo.LeftFootOffset = 0.f;
			DesiredFootIKInfo.ZOffset = 0.f;
			DesiredFootIKInfo.LeftFootIKAlpha = 0.f;
		}
		else
		{
			DesiredFootIKInfo.ZOffset = RightHitResult.Location.Z - RightFootLocation.Z;
			DesiredFootIKInfo.LeftFootIKAlpha = 1.f;
		}
	}
	else
	{
		DesiredFootIKInfo.RightFootOffset = (RightHitResult.Location.Z - LeftHitResult.Location.Z) * -1.f;
		if (DesiredFootIKInfo.RightFootOffset < -41.f)
		{
			DesiredFootIKInfo.RightFootOffset = 0.f;
			DesiredFootIKInfo.ZOffset = 0.f;
			DesiredFootIKInfo.RightFootIKAlpha = 0.f;
		}
		else
		{
			DesiredFootIKInfo.ZOffset = LeftHitResult.Location.Z - LeftFootLocation.Z;
			DesiredFootIKInfo.RightFootIKAlpha = 1.f;
		}
	}

	DesiredFootIKInfo.LeftFootAngle = FRotator(
		UKismetMathLibrary::DegAtan2(LeftHitResult.Normal.X, LeftHitResult.Normal.Z) * -1.f,
		0.f,
		UKismetMathLibrary::DegAtan2(LeftHitResult.Normal.Y, LeftHitResult.Normal.Z)
	);

	DesiredFootIKInfo.RightFootAngle = FRotator(
		UKismetMathLibrary::DegAtan2(RightHitResult.Normal.X, RightHitResult.Normal.Z) * -1.f,
		0.f,
		UKismetMathLibrary::DegAtan2(RightHitResult.Normal.Y, RightHitResult.Normal.Z)
	);

	return CalculateFootIKInterpolation(Deltatime, CurrentFootIKInfo, DesiredFootIKInfo);
}

FHumanFootIKInfo FHumanFootIKHelper::CalculateFootIKInterpolation(float DeltaTime, FHumanFootIKInfo CurrentFootIKInfo,
	FHumanFootIKInfo DesiredFootIKInfo)
{
	FHumanFootIKInfo Result;

	const float InterpSpeed = 30.f;

	Result.ZOffset = FMath::FInterpTo(CurrentFootIKInfo.ZOffset, DesiredFootIKInfo.ZOffset, DeltaTime, InterpSpeed);
	Result.LeftFootIKAlpha = FMath::FInterpTo(CurrentFootIKInfo.LeftFootIKAlpha, DesiredFootIKInfo.LeftFootIKAlpha,
                                              DeltaTime, InterpSpeed);
	Result.LeftFootOffset = FMath::FInterpTo(CurrentFootIKInfo.LeftFootOffset, DesiredFootIKInfo.LeftFootOffset,
                                             DeltaTime, InterpSpeed);
	Result.LeftFootAngle = FMath::RInterpTo(CurrentFootIKInfo.LeftFootAngle, DesiredFootIKInfo.LeftFootAngle, DeltaTime,
                                            InterpSpeed);
	Result.RightFootIKAlpha = FMath::FInterpTo(CurrentFootIKInfo.RightFootIKAlpha, DesiredFootIKInfo.RightFootIKAlpha,
                                               DeltaTime, InterpSpeed);
	Result.RightFootOffset = FMath::FInterpTo(CurrentFootIKInfo.RightFootOffset, DesiredFootIKInfo.RightFootOffset,
                                              DeltaTime, InterpSpeed);
	Result.RightFootAngle = FMath::RInterpTo(CurrentFootIKInfo.RightFootAngle, DesiredFootIKInfo.RightFootAngle,
                                             DeltaTime, InterpSpeed);

	return Result;
}

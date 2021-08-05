// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/AnimNotify/CAnimNotifyState_SetDistance.h"
#include "Kismet/KismetSystemLibrary.h"

void UCAnimNotifyState_SetDistance::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	AActor* ThisActor = MeshComp->GetOwner();

	if(ThisActor == nullptr)
	{
		return;
	}

	bIsGameWorld = true;
	
	ActorOriginLocation = ThisActor->GetActorLocation();
	ActorForwardVector = ThisActor->GetActorForwardVector();
	
	FRawCurveTracks CurveTracks = Animation->GetCurveData();
	TArray<FFloatCurve> Curves = CurveTracks.FloatCurves;

	check(Curves.Num() > 0);
	
	DistanceCurve = Curves[0];
	ProcessingTime = 0.f;
}

void UCAnimNotifyState_SetDistance::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	if(bIsGameWorld == false)
	{
		return;
	}
	
	ProcessingTime += FrameDeltaTime;

	float DistanceFromOrigin = DistanceCurve.Evaluate(ProcessingTime);

	FVector NewActorLocation = ActorOriginLocation + ActorForwardVector * DistanceFromOrigin;

	MeshComp->GetOwner()->SetActorLocation(NewActorLocation, true);
}

void UCAnimNotifyState_SetDistance::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	return;
}

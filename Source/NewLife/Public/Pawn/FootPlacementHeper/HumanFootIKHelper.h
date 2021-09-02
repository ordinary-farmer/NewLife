// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HumanFootIkInfo.h"

#define LEFT_FOOT_SOCK_NAME (FName(TEXT("foot_l")))
#define RIGHT_FOOT_SOCK_NAME (FName(TEXT("foot_r")))
#define IK_FOOT_ROOT_SOCK_NAME (FName(TEXT("ik_foot_root")))

/**
* 인간형 캐릭터의 FootPlacement 계산을 도와주는 클래스입니다.
* 이 클래스를 사용하는 Mesh의 Skeleton은 반드시 "foot_l", "foot_r", "ik_foot_root"을 포함해야 합니다.
*/
class NEWLIFE_API FHumanFootIKHelper
{
public:
	FHumanFootIKHelper();
	virtual ~FHumanFootIKHelper();

	FHumanFootIKInfo UpdateFootIKInfo(UWorld* World, ACharacter* Character, FHumanFootIKInfo CurrentFootIKInfo,
	                                  float Deltatime);

private:
	FHumanFootIKInfo CalculateFootIKInterpolation(float DeltaTime, FHumanFootIKInfo CurrentFootIKInfo,
	                                              FHumanFootIKInfo DesiredFootIKInfo);

	static const float TraceDistanceFromFoot;
};

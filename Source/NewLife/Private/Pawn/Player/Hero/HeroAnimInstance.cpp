// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/Hero/HeroAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pawn/Player/Components/WeaponMeshComponent.h"
#include "Pawn/Player/Hero/Hero.h"

UHeroAnimInstance::UHeroAnimInstance()
{
	FootIKManager = MakeUnique<FHumanFootIKHelper>();

	static ConstructorHelpers::FObjectFinder<UAnimMontage> UnArmMontageAsset(TEXT("AnimMontage'/Game/Paladin/Animation/Montages/AM_Unarm.AM_Unarm'"));
	if(UnArmMontageAsset.Succeeded())
	{
		UnArmMontage = UnArmMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("AnimMontage'/Game/Paladin/Animation/Montages/AM_Equip.AM_Equip'"));
	if(EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}
}

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AHero* TmpOwner = Cast<AHero>(TryGetPawnOwner());

	if (TmpOwner == nullptr)
	{
		return;
	}

	Owner = TmpOwner;		
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if(Owner == nullptr)
	{
		return;
	}

	Speed = Owner->GetLocomotionInfo().Speed;
	Gait = Owner->GetLocomotionInfo().Gait;
	Acceleration = Owner->GetLocomotionInfo().Acceleration;
	bIsMoving = Owner->GetLocomotionInfo().bIsMoving;
	bIsAccelerating = Owner->GetLocomotionInfo().bIsAccelerating;
	bIsInAir = Owner->GetLocomotionInfo().bIsInAir;
	bPressedJump = Owner->GetLocomotionInfo().bPressedJump;
	bPressedSprint = Owner->GetLocomotionInfo().bPressedSprint;
	bIsCarryingWeapon = Owner->GetLocomotionInfo().bIsCarryingWeapon;

	if(bIsCarryingWeapon)
	{
		Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());
	}
	// Place Foot By Using FFootIKHelper	
	if (!bIsInAir && !bIsMoving)
	{
		FootIKInfo = FootIKManager->UpdateFootIKInfo(GetWorld(), Owner, FootIKInfo, DeltaTime);
	}
	else
	{
		const FHumanFootIKInfo EmptyFootIKInfo;
		FootIKInfo = EmptyFootIKInfo;
	}
}

void UHeroAnimInstance::PlayUnArmMontage()
{
	Montage_Play(UnArmMontage);
}

void UHeroAnimInstance::PlayEquipMontage()
{
	Montage_Play(EquipMontage);
}

void UHeroAnimInstance::ChooseMoveEndAnimation()
{
	if(Speed > 275.f)
	{
		bShouldPlayRunEnd = true;
	}
	else
	{
		bShouldPlayRunEnd = false;
	}

	if(Speed > 600.f)
	{
		RunEndPlayRate = 1.2f;
	}
	else
	{
		RunEndPlayRate = 1.55f;
	}
}

void UHeroAnimInstance::AnimNotify_MoveStartToMoveEnd()
{
	ChooseMoveEndAnimation();
}

void UHeroAnimInstance::AnimNotify_MovingOut()
{
	ChooseMoveEndAnimation();
}

void UHeroAnimInstance::AnimNotify_MoveEndIn()
{
	Owner->GetCharacterMovement()->bUseSeparateBrakingFriction = true;
	Owner->GetCharacterMovement()->BrakingFriction = 1.3f;
	
	if(bShouldPlayRunEnd)
	{
		Owner->GetCharacterMovement()->BrakingDecelerationWalking = 64.f;
	}
	else
	{
		Owner->GetCharacterMovement()->BrakingDecelerationWalking = 512.f;
	}
}

void UHeroAnimInstance::AnimNotify_MoveEndOut()
{
	Owner->GetCharacterMovement()->bUseSeparateBrakingFriction = false;
	Owner->GetCharacterMovement()->BrakingFriction = 0.f;
	Owner->GetCharacterMovement()->BrakingDecelerationWalking = 2048.f;
}

void UHeroAnimInstance::AnimNotify_LandIn()
{
	Owner->GetCharacterMovement()->bUseSeparateBrakingFriction = false;
	Owner->GetCharacterMovement()->BrakingFriction = 0.f;
	Owner->GetCharacterMovement()->BrakingDecelerationWalking = 2048.f;
	
	Owner->SetShouldBlockMoveInput(true);	
}

void UHeroAnimInstance::AnimNotify_LandOut()
{
	Owner->SetShouldBlockMoveInput(false);
}

void UHeroAnimInstance::AnimNotify_Equip()
{
	check(Owner);
	
	USkeletalMeshComponent* OwnerMeshComp = GetSkelMeshComponent();
	check(OwnerMeshComp);
	
	UWeaponMeshComponent* RightHandMeshComp = Owner->GetRightHandWeaponMeshComponent();
	check(RightHandMeshComp);

	UWeaponMeshComponent* LeftHandMeshComp = Owner->GetLeftHandWeaponMeshComponent();
	check(LeftHandMeshComp);

	RightHandMeshComp->AttachToPalm();
	LeftHandMeshComp->AttachToPalm();
}

void UHeroAnimInstance::AnimNotify_UnArm()
{
	check(Owner);
	
	USkeletalMeshComponent* OwnerMeshComp = GetSkelMeshComponent();
	check(OwnerMeshComp);
	
	UWeaponMeshComponent* RightHandMeshComp = Owner->GetRightHandWeaponMeshComponent();
	check(RightHandMeshComp);

	UWeaponMeshComponent* LeftHandMeshComp = Owner->GetLeftHandWeaponMeshComponent();
	check(LeftHandMeshComp);

	RightHandMeshComp->AttachToBack();
	LeftHandMeshComp->AttachToBack();
}

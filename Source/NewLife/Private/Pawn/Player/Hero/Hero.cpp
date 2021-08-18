// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Player/Hero/Hero.h"
#include "Pawn/Player/Hero/HeroSpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Pawn/Player/Components/InteractHelperWidgetComponent.h"
#include "Pawn/Player/Components/InteractComponent.h"
#include "Pawn/Player/Components/WeaponMeshComponent.h"
#include "Pawn/Player/Hero/HeroAnimInstance.h"

// Sets default values
AHero::AHero()
	: MaxWalkingSpeed(190.f)
	  , MaxRunningSpeed(600.f)
	  , MaxSprintingSpeed(900.f)
	  , MaxWalkingAcceleration(512.f)
	  , MaxRunningAcceleration(2048.f)
	  , XInput(0.f)
	  , YInput(0.f)
	  , CameraTurnRate(1.f)
	  , CameraLookUpRate(1.f)
	  , bShouldBlockMoveInput(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightHandWeaponMeshComp = CreateDefaultSubobject<UWeaponMeshComponent>(TEXT("RightHandWeaponMeshComp"));
	RightHandWeaponMeshComp->SetupAttachment(GetMesh());
	
	LeftHandWeaponMeshComp = CreateDefaultSubobject<UWeaponMeshComponent>(TEXT("LeftHandWeaponMeshComp"));
	LeftHandWeaponMeshComp->SetupAttachment(GetMesh());

	HeadMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMeshComp"));
	HeadMeshComp->SetupAttachment(GetMesh());

	ShoulderMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderMeshComp"));
	ShoulderMeshComp->SetupAttachment(GetMesh());

	ArmMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmMeshComp"));
	ArmMeshComp->SetupAttachment(GetMesh());

	TorsoMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TorsoMeshComp"));
	TorsoMeshComp->SetupAttachment(GetMesh());

	CameraBoom = CreateDefaultSubobject<UHeroSpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));

	InteractHelperWidget = CreateDefaultSubobject<UInteractHelperWidgetComponent>(TEXT("InteractHelperWidget"));
	InteractHelperWidget->SetupAttachment(RootComponent);
	//InteractHelperWidget->SetRelativeLocation(FVector(0.f, 0.f, 90.f));

	InteractComp = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComp"));
	bUseControllerRotationYaw = false;
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocomotionInfo();

	TurnAndMove(DeltaTime);
}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AHero::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AHero::LookUpAtRate);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHero::UpdateXInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHero::UpdateYInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHero::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHero::StopJump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHero::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHero::StopSprint);
	PlayerInputComponent->BindAction("ToggleGait", IE_Pressed, this, &AHero::ToggleWalkOrRun);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractComp, &UInteractComponent::Interact);
	PlayerInputComponent->BindAction("ToggleWeaponCarryMode", IE_Pressed, this, &AHero::ToggleWeaponCarryMode);
}

void AHero::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();

	
	
	// FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, false);
	//
	// RightHandWeaponMeshComp->AttachToComponent(GetMesh(), TransformRules, FName("RightHand2"));
	// LeftHandWeaponMeshComp->AttachToComponent(GetMesh(), TransformRules, FName("LeftHand2"));
}

void AHero::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	TorsoMesh = MergeSkeletalMeshes(TorsoMeshMergeParam);
	HeadMesh = MergeSkeletalMeshes(HeadMeshMergeParam);
	ShoulderMesh = MergeSkeletalMeshes(ShoulderMeshMergeParam);
	LegMesh = MergeSkeletalMeshes(LegMeshMergeParam);
	ArmMesh = MergeSkeletalMeshes(ArmMeshMergeParam);
	
	GetMesh()->SetSkeletalMesh(LegMesh);
	HeadMeshComp->SetSkeletalMesh(HeadMesh);
	ShoulderMeshComp->SetSkeletalMesh(ShoulderMesh);
	ArmMeshComp->SetSkeletalMesh(ArmMesh);
	TorsoMeshComp->SetSkeletalMesh(TorsoMesh);
	
	HeadMeshComp->SetMasterPoseComponent(GetMesh());
	ShoulderMeshComp->SetMasterPoseComponent(GetMesh());
	ArmMeshComp->SetMasterPoseComponent(GetMesh());
	TorsoMeshComp->SetMasterPoseComponent(GetMesh());

	RightHandWeaponMeshComp->InitWeaponMesh(GetMesh(), EHeroHandType::RightHand);
	LeftHandWeaponMeshComp->InitWeaponMesh(GetMesh(), EHeroHandType::LeftHand);
}

USkeletalMesh* AHero::MergeSkeletalMeshes(const FSkeletalMeshMergeParams& MeshMergeParams)
{
	if(MeshMergeParams.MeshesToMerge.Num() == 0)
	{
		return nullptr;
	}
	else if(MeshMergeParams.MeshesToMerge.Num() == 1)
	{
		return MeshMergeParams.MeshesToMerge[0];
	}

	USkeletalMesh* Result = UMeshMergeFunctionLibrary::MergeMeshes(MeshMergeParams);
	return Result;
}

void AHero::UpdateLocomotionInfo()
{
	LocomotionInfo.Speed = GetVelocity().Size();

	if (LocomotionInfo.Speed > 0.f)
	{
		LocomotionInfo.bIsMoving = true;
	}
	else
	{
		LocomotionInfo.bIsMoving = false;
	}

	LocomotionInfo.Acceleration = GetCharacterMovement()->GetCurrentAcceleration().Size();
	if (LocomotionInfo.Acceleration > 0.f)
	{
		LocomotionInfo.bIsAccelerating = true;
	}
	else
	{
		LocomotionInfo.bIsAccelerating = false;
	}

	LocomotionInfo.bIsInAir = GetCharacterMovement()->IsFalling();
	LocomotionInfo.bMoveInput = XInput != 0 || YInput != 0;
}

void AHero::TurnAndMove(float DeltaTime)
{
	const FRotator CameraWorldRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardBasedXInput(FRotationMatrix(CameraWorldRotation).GetScaledAxis(EAxis::X) * XInput);
	const FVector RightBasedYInput(FRotationMatrix(CameraWorldRotation).GetScaledAxis(EAxis::Y) * YInput);

	FVector DirectionToMove(ForwardBasedXInput + RightBasedYInput);
	DirectionToMove.Normalize();

	// Turn My Self
	if (LocomotionInfo.bIsMoving && LocomotionInfo.bMoveInput)
	{
		FRotator TurnTo;
		
		if(LocomotionInfo.bIsCarryingWeapon)
		{
			const FVector CameraForwardVector(FRotationMatrix(CameraWorldRotation).GetScaledAxis(EAxis::X));

			TurnTo = FRotator(FMath::RInterpTo(GetActorRotation(), CameraForwardVector.Rotation(), DeltaTime,
                                         HERO_TURN_RATE));
		}
		else
		{
			TurnTo = FRotator(FMath::RInterpTo(GetActorRotation(), DirectionToMove.Rotation(), DeltaTime,
                                         HERO_TURN_RATE));
		}

		TurnTo.Pitch = 0.f;
		SetActorRotation(TurnTo);
	}
	
	// Move My Self
	float MoveAmount;
	if (XInput == 0 || YInput == 0)
	{
		MoveAmount = FMath::Abs(XInput) + FMath::Abs(YInput);
	}
	else
	{
		MoveAmount = (FMath::Abs(XInput) + FMath::Abs(YInput)) / 2;
	}

	if(LocomotionInfo.bIsCarryingWeapon)
	{
		if(FVector::DotProduct(GetActorForwardVector(), DirectionToMove) < -0.01f)
		{
			MoveAmount *= .75f;
		}
		else
		{
			MoveAmount *= .9f;
		}
	}

	AddMovementInput(DirectionToMove, MoveAmount);
}

void AHero::InterpolateMaxSpeed()
{
	const float NewMaxSpeed = FMath::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, TargetGaitMaxSpeed,
	                                           GetWorld()->DeltaTimeSeconds, 10.f);
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;

	const float NewMaxAcceleration = FMath::FInterpTo(GetCharacterMovement()->MaxAcceleration,
	                                                  TargetGaitMaxAcceleration, GetWorld()->DeltaTimeSeconds, 10.f);
	GetCharacterMovement()->MaxAcceleration = NewMaxAcceleration;

	if (FMath::IsNearlyEqual(GetCharacterMovement()->MaxWalkSpeed, TargetGaitMaxSpeed) && FMath::IsNearlyEqual(
		GetCharacterMovement()->MaxAcceleration, TargetGaitMaxAcceleration))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_ToggleGaitTick);
	}
}

void AHero::ToggleGait(EHeroGait NewGait)
{
	if(LocomotionInfo.Gait == NewGait)
	{
		return;
	}
	
	if (LocomotionInfo.Gait != EHeroGait::Sprinting && NewGait == EHeroGait::Sprinting)
	{
		CameraBoom->SetCamMoveMode(ECamMoveMode::Sprint);
	}
	else if (LocomotionInfo.Gait == EHeroGait::Sprinting && NewGait != EHeroGait::Sprinting)
	{
		CameraBoom->SetCamMoveMode(ECamMoveMode::Normal);
	}

	LocomotionInfo.Gait = NewGait;

	float MaxSpeed = 0.f;
	float MaxAcceleration = 0.f;

	switch (NewGait)
	{
	case EHeroGait::Walking:
		MaxSpeed = MaxWalkingSpeed;
		MaxAcceleration = MaxWalkingAcceleration;
		break;
	case EHeroGait::Running:
		MaxSpeed = MaxRunningSpeed;
		MaxAcceleration = MaxRunningAcceleration;
		break;
	case EHeroGait::Sprinting:
		MaxSpeed = MaxSprintingSpeed;
		MaxAcceleration = MaxRunningAcceleration;
		break;
	default:
		checkNoEntry();
	}

	if (GetWorldTimerManager().IsTimerActive(TimerHandle_ToggleGaitTick))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_ToggleGaitTick);
	}

	TargetGaitMaxSpeed = MaxSpeed;
	TargetGaitMaxAcceleration = MaxAcceleration;

	check(TargetGaitMaxSpeed != 0.f);
	check(TargetGaitMaxAcceleration != 0.f);

	GetWorldTimerManager().SetTimer(TimerHandle_ToggleGaitTick, this, &AHero::InterpolateMaxSpeed,
	                                GetWorld()->DeltaTimeSeconds, true);
}

void AHero::SetRightHandWeaponMesh(UStaticMesh* LoadedMesh)
{
	RightHandWeaponMeshComp->SetStaticMesh(LoadedMesh);
}

void AHero::SetLeftHandWeaponMesh(UStaticMesh* LoadedMesh)
{
	LeftHandWeaponMeshComp->SetStaticMesh(LoadedMesh);
}

void AHero::SetHeadMesh(USkeletalMesh* LoadedMesh)
{
	if(LoadedMesh == nullptr)
	{
		HeadMeshComp->SetSkeletalMesh(HeadMesh);
	}
	else
	{
		HeadMeshComp->SetSkeletalMesh(LoadedMesh);
	}
}

void AHero::SetShoulderMesh(USkeletalMesh* LoadedMesh)
{
	if(LoadedMesh == nullptr)
	{
		ShoulderMeshComp->SetSkeletalMesh(ShoulderMesh);
	}
	else
	{
		ShoulderMeshComp->SetSkeletalMesh(LoadedMesh);
	}
}

void AHero::SetTorsoMesh(USkeletalMesh* LoadedMesh)
{
	if(LoadedMesh == nullptr)
	{
		TorsoMeshComp->SetSkeletalMesh(TorsoMesh);
	}
	else
	{
		TorsoMeshComp->SetSkeletalMesh(LoadedMesh);
	}
}

void AHero::SetLegMesh(USkeletalMesh* LoadedMesh)
{
	if(LoadedMesh == nullptr)
	{
		GetMesh()->SetSkeletalMesh(LegMesh);
	}
	else
	{
		GetMesh()->SetSkeletalMesh(LoadedMesh);
	}
}

void AHero::SetArmMesh(USkeletalMesh* LoadedMesh)
{
	if(LoadedMesh == nullptr)
	{
		ArmMeshComp->SetSkeletalMesh(ArmMesh);
	}
	else
	{
		ArmMeshComp->SetSkeletalMesh(LoadedMesh);
	}
}

void AHero::UpdateXInput(float Value)
{
	if (bShouldBlockMoveInput || bShouldBlockAllInput)
	{
		XInput = 0.f;
	}
	else
	{
		XInput = Value;
	}
}

void AHero::UpdateYInput(float Value)
{
	if (bShouldBlockMoveInput || bShouldBlockAllInput)
	{
		YInput = 0.f;
	}
	else
	{
		YInput = Value;
	}
}

void AHero::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * CameraTurnRate);
}

void AHero::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * CameraLookUpRate);
}

void AHero::StartJump()
{
	LocomotionInfo.bPressedJump = true;
}

void AHero::StopJump()
{
	LocomotionInfo.bPressedJump = false;
}

void AHero::StartSprint()
{
	if (LocomotionInfo.Gait == EHeroGait::Walking || GetCharacterMovement()->IsFalling() || bShouldBlockAllInput)
	{
		return;
	}

	LocomotionInfo.bPressedSprint = true;

	ToggleGait(EHeroGait::Sprinting);
}

void AHero::StopSprint()
{
	if (LocomotionInfo.Gait == EHeroGait::Walking || GetCharacterMovement()->IsFalling() || bShouldBlockAllInput)
	{
		return;
	}

	LocomotionInfo.bPressedSprint = false;

	ToggleGait(EHeroGait::Running);
}

void AHero::ToggleWalkOrRun()
{
	if (GetCharacterMovement()->IsFalling() || bShouldBlockAllInput || LocomotionInfo.bIsCarryingWeapon)
	{
		return;
	}

	if (LocomotionInfo.Gait == EHeroGait::Walking)
	{
		ToggleGait(EHeroGait::Running);
	}
	else
	{
		ToggleGait(EHeroGait::Walking);
	}
}

void AHero::ToggleWeaponCarryMode()
{
	if(LocomotionInfo.bIsInAir == true || LocomotionInfo.Speed > 0.f)
	{
		return;
	}
	
	UHeroAnimInstance* AnimInstance = Cast<UHeroAnimInstance>(GetMesh()->GetAnimInstance());
	check(AnimInstance);

	if(LocomotionInfo.bIsCarryingWeapon)
	{
		AnimInstance->PlayUnArmMontage();
		LocomotionInfo.bIsCarryingWeapon = false;
	}
	else
	{
		AnimInstance->PlayEquipMontage();
		LocomotionInfo.bIsCarryingWeapon = true;
		ToggleGait(EHeroGait::Running);
	}
}

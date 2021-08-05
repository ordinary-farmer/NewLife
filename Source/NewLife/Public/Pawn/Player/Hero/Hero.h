// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroLocomotionInfo.h"
#include "BlueprintFunctionLibrary/MeshMergeFunctionLibrary.h"
#include "Hero.generated.h"

#define HERO_TURN_RATE (10.f)

class UHeroSpringArmComponent;
class UCameraComponent;
class UInputHandlerComponent;
class USphereComponent;
class UHeroStatsComponent;
class UWidgetComponent;
class UInteractComponent;
class UInteractHelperWidgetComponent;

UCLASS()
class NEWLIFE_API AHero : public ACharacter
{
	GENERATED_BODY()

	// ******************** Variables... ************************
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* RightHandWeaponMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* LeftHandWeaponMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* HeadMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* ShoulderMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* ArmMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* TorsoMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	UHeroSpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	USphereComponent* AgroSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Locomotion", meta=(AllowPrivateAccess="true"))
	FHeroLocomotionInfo LocomotionInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | Locomotion", meta=(AllowPrivateAccess="true"))
	float MaxWalkingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | Locomotion", meta=(AllowPrivateAccess="true"))
	float MaxRunningSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | Locomotion", meta=(AllowPrivateAccess="true"))
	float MaxSprintingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | Locomotion", meta=(AllowPrivateAccess="true"))
	float MaxWalkingAcceleration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | Locomotion", meta=(AllowPrivateAccess="true"))
	float MaxRunningAcceleration;

	float TargetGaitMaxSpeed;
	float TargetGaitMaxAcceleration;

	FTimerHandle TimerHandle_ToggleGaitTick;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	UInteractHelperWidgetComponent* InteractHelperWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Components", meta=(AllowPrivateAccess="true"))
	UInteractComponent* InteractComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	FSkeletalMeshMergeParams TorsoMeshMergeParam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	FSkeletalMeshMergeParams HeadMeshMergeParam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	FSkeletalMeshMergeParams ShoulderMeshMergeParam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	FSkeletalMeshMergeParams ArmMeshMergeParam;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	FSkeletalMeshMergeParams LegMeshMergeParam;

	UPROPERTY(BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	USkeletalMesh* TorsoMesh;

	UPROPERTY(BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	USkeletalMesh* HeadMesh;

	UPROPERTY(BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	USkeletalMesh* ShoulderMesh;

	UPROPERTY(BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	USkeletalMesh* ArmMesh;

	UPROPERTY(BlueprintReadOnly, Category="Hero | DefaultMesh", meta=(AllowPrivateAccess="true"))
	USkeletalMesh* LegMesh;

public:
	// ******************** Methods... ************************

	AHero();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	USkeletalMesh* MergeSkeletalMeshes(const FSkeletalMeshMergeParams& MeshMergeParams);
	
	void UpdateLocomotionInfo();

	void TurnAndMove(float DeltaTime);

	void InterpolateMaxSpeed();

	void ToggleGait(EHeroGait NewGait);

public:
	// ******************** Getters and Setters... ************************

	FHeroLocomotionInfo GetLocomotionInfo() const { return LocomotionInfo; }

	FORCEINLINE void SetShouldBlockMoveInput(bool NewState) { bShouldBlockMoveInput = NewState; }

	FORCEINLINE float GetMaxWalkingSpeed() const { return MaxWalkingSpeed; }
	FORCEINLINE float GetMaxRunningSpeed() const { return MaxRunningSpeed; }
	FORCEINLINE float GetMaxSprintingSpeed() const { return MaxSprintingSpeed; }
	
	FORCEINLINE UStaticMeshComponent* GetRightHandWeaponMeshComponent() const { return RightHandWeaponMeshComp; }
	void SetRightHandWeaponMesh(UStaticMesh* LoadedMesh);
	
	FORCEINLINE UStaticMeshComponent* GetLeftHandWeaponMeshComponent() const { return LeftHandWeaponMeshComp; }
	void SetLeftHandWeaponMesh(UStaticMesh* LoadedMesh);
	
	FORCEINLINE USkeletalMeshComponent* GetHeadMeshComponent() const { return HeadMeshComp; }
	void SetHeadMesh(USkeletalMesh* LoadedMesh);
	
	FORCEINLINE USkeletalMeshComponent* GetShoulderMeshComponent() const { return ShoulderMeshComp; }
	void SetShoulderMesh(USkeletalMesh* LoadedMesh);
	
	FORCEINLINE USkeletalMeshComponent* GetTorsoMeshComponent() const { return TorsoMeshComp; }
	void SetTorsoMesh(USkeletalMesh* LoadedMesh);
	
	FORCEINLINE USkeletalMeshComponent* GetLegMeshComponent() const { return GetMesh(); }
	void SetLegMesh(USkeletalMesh* LoadedMesh);
	
	FORCEINLINE USkeletalMeshComponent* GetArmMeshComponent() const { return ArmMeshComp; }
	void SetArmMesh(USkeletalMesh* LoadedMesh);

private:
	// ******************** Input Variables and Functions... ***************

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Input", meta=(AllowPrivateAccess="true"))
	float XInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Input", meta=(AllowPrivateAccess="true"))
	float YInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Hero | Input", meta=(AllowPrivateAccess="true"))
	float CameraTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Hero | Input", meta=(AllowPrivateAccess="true"))
	float CameraLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Hero | Input", meta=(AllowPrivateAccess="true"))
	bool bShouldBlockMoveInput;

	void UpdateXInput(float Value);

	void UpdateYInput(float Value);

	void TurnAtRate(float Value);

	void LookUpAtRate(float Value);

	void StartJump();

	void StopJump();

	void StartSprint();

	void StopSprint();

	void ToggleWalkOrRun();
};

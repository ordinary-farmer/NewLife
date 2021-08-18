// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponMeshComponent.generated.h"

#define RIGHT_HAND_PALM_SOCKET_NAME (FName("RightHand1"))
#define RIGHT_HAND_BACK_SOCKET_NAME (FName("RightHand2"))
#define LEFT_HAND_PALM_SOCKET_NAME (FName("LeftHand1"))
#define LEFT_HAND_BACK_SOCKET_NAME (FName("LeftHand2"))

class USkeletalMesh;

UENUM()
enum class EHeroHandType
{
	None,
	RightHand,
	LeftHand
};

/**
 * 
 */
UCLASS()
class NEWLIFE_API UWeaponMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY()
	USkeletalMeshComponent* OwnerCharacterMesh;

	EHeroHandType HandType;
	
public:
	UWeaponMeshComponent();
	
	void InitWeaponMesh(USkeletalMeshComponent* NewOwnerCharacterMesh, EHeroHandType NewHandType);

	void AttachToPalm();

	void AttachToBack();

	void ActivateWeaponCollision();

	void DeactivateWeaponCollision();
};

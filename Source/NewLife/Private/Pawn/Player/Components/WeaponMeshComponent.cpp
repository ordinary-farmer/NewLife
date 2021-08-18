// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Pawn/Player/Components/WeaponMeshComponent.h"


UWeaponMeshComponent::UWeaponMeshComponent()
	: OwnerCharacterMesh(nullptr)
	  , HandType(EHeroHandType::None)
{
}

void UWeaponMeshComponent::InitWeaponMesh(USkeletalMeshComponent* NewOwnerCharacterMesh, EHeroHandType NewHandType)
{
	check(NewOwnerCharacterMesh);
	OwnerCharacterMesh = NewOwnerCharacterMesh;

	check(NewHandType != EHeroHandType::None);

	HandType = NewHandType;

	AttachToBack();
}

void UWeaponMeshComponent::AttachToPalm()
{
	FName PalmSocketName;
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, false);

	switch (HandType)
	{
	case EHeroHandType::LeftHand:
		PalmSocketName = LEFT_HAND_PALM_SOCKET_NAME;
		break;
	case EHeroHandType::RightHand:
		PalmSocketName = RIGHT_HAND_PALM_SOCKET_NAME;
		break;
	default:
		checkNoEntry();
	}

	AttachToComponent(OwnerCharacterMesh, TransformRules, PalmSocketName);
}

void UWeaponMeshComponent::AttachToBack()
{
	FName BackSocketName;
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, false);
	
	switch (HandType)
	{
	case EHeroHandType::LeftHand:
		BackSocketName = LEFT_HAND_BACK_SOCKET_NAME;
		break;
	case EHeroHandType::RightHand:
		BackSocketName = RIGHT_HAND_BACK_SOCKET_NAME;
		break;
	default:
		checkNoEntry();
	}

	AttachToComponent(OwnerCharacterMesh, TransformRules, BackSocketName);
}

void UWeaponMeshComponent::ActivateWeaponCollision()
{
}

void UWeaponMeshComponent::DeactivateWeaponCollision()
{
}

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_HeroBlockMoveInput.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UCAnimNotify_HeroBlockMoveInput : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

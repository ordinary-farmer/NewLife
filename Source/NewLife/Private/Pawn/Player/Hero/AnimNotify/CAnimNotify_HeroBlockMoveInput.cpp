// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Pawn/Player/Hero/AnimNotify/CAnimNotify_HeroBlockMoveInput.h"
#include "Pawn/Player/Hero/Hero.h"

void UCAnimNotify_HeroBlockMoveInput::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AHero* PlayerCharacter = Cast<AHero>(MeshComp->GetOwner());

	if(PlayerCharacter)
	{
		PlayerCharacter->SetShouldBlockMoveInput(true);
	}
}

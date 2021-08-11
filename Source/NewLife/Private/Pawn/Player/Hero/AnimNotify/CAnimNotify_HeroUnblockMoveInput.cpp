// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Pawn/Player/Hero/AnimNotify/CAnimNotify_HeroUnblockMoveInput.h"
#include "Pawn/Player/Hero/Hero.h"

void UCAnimNotify_HeroUnblockMoveInput::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AHero* PlayerCharacter = Cast<AHero>(MeshComp->GetOwner());

	if(PlayerCharacter)
	{
		PlayerCharacter->SetShouldBlockMoveInput(false);
	}
}

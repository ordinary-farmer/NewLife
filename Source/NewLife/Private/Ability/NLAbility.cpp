// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Ability/NLAbility.h"

UNLAbility::UNLAbility()
{
}

bool UNLAbility::TryExecute(ANLPlayerController* PlayerController)
{
	GenerateEffects();

	return true;
}

void UNLAbility::GenerateEffects()
{
}

bool UNLAbility::IsExecutable(ANLPlayerController* PlayerController)
{
	return true;
}

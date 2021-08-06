// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Ability/PlayerAbility/PlayerTemporaryBuffAbility.h"

UPlayerTemporaryBuffAbility::UPlayerTemporaryBuffAbility()
{
}

void UPlayerTemporaryBuffAbility::Execute()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerTemporaryBuffAbility Execute!"));
}

void UPlayerTemporaryBuffAbility::OnBuffExpired()
{
}

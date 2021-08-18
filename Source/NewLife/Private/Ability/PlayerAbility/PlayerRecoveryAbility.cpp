// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Ability/PlayerAbility/PlayerRecoveryAbility.h"
#include "Controller/Player/NLPlayerController.h"
#include "Controller/Player/Component/HeroStatComponent.h"
#include "Singleton/GameplayMessageHandlerSubsystem.h"

UPlayerRecoveryAbility::UPlayerRecoveryAbility()
{
}

bool UPlayerRecoveryAbility::TryExecute(ANLPlayerController* PlayerController)
{
	bool Result = Super::TryExecute(PlayerController);

	const bool bIsExecutable = IsExecutable(PlayerController);

	Result = Result && bIsExecutable;

	if (bIsExecutable && PlayerController)
	{
		UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();

		switch (RecoveryType)
		{
		case EPlayerRecovery::HealthPoint:
			HeroStatComp->RecoverHealth(RecoveryValue);
			break;
		case EPlayerRecovery::ManaPoint:
			HeroStatComp->RecoverMana(RecoveryValue);
			break;
		default:
			checkNoEntry();
		}
	}

	return Result;	
}

bool UPlayerRecoveryAbility::IsExecutable(ANLPlayerController* PlayerController)
{
	bool Result = Super::IsExecutable(PlayerController);

	UHeroStatComponent* HeroStatComp = PlayerController->GetHeroStatComp();

	switch (RecoveryType)
	{
	case EPlayerRecovery::HealthPoint:
		Result = Result && HeroStatComp->GetMaxHealthPoint() > HeroStatComp->GetCurrentHealthPoint();

		if (Result == false)
		{
			UGameInstance* GameInstance = PlayerController->GetGameInstance();
			UGameplayMessageHandlerSubsystem* MessageHandler = GameInstance->GetSubsystem<
				UGameplayMessageHandlerSubsystem>();

			MessageHandler->DisplayMessage("FullHealthPoint");
		}
		break;
	case EPlayerRecovery::ManaPoint:
		Result = Result && HeroStatComp->GetMaxManaPoint() > HeroStatComp->GetCurrentManaPoint();

		if (Result == false)
		{
			UGameInstance* GameInstance = PlayerController->GetGameInstance();
			UGameplayMessageHandlerSubsystem* MessageHandler = GameInstance->GetSubsystem<
				UGameplayMessageHandlerSubsystem>();

			MessageHandler->DisplayMessage("FullManaPoint");
		}
		break;
	default:
		checkNoEntry();
	}
	
	return Result;
}

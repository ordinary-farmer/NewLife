// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Ability/NLAbility.h"
#include "EPlayerRecovery.h"
#include "PlayerRecoveryAbility.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UPlayerRecoveryAbility : public UNLAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EPlayerRecovery RecoveryType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float RecoveryValue;

	public:
	UPlayerRecoveryAbility();

	virtual void Execute() override;
};

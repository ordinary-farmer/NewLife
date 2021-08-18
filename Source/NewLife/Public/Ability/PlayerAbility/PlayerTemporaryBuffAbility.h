// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Ability/NLAbility.h"
#include "EPlayerTemporaryBuff.h"
#include "PlayerTemporaryBuffAbility.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UPlayerTemporaryBuffAbility : public UNLAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EPlayerTemporaryBuff BuffType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float BuffValue;

public:
	UPlayerTemporaryBuffAbility();

private:
	void OnBuffExpired();
};

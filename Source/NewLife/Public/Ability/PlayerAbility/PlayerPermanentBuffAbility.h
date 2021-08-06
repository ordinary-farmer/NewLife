// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Ability/NLAbility.h"
#include "EPlayerPermanentBuff.h"
#include "PlayerPermanentBuffAbility.generated.h"

/**
 * 
 */
UCLASS()
class NEWLIFE_API UPlayerPermanentBuffAbility : public UNLAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	EPlayerPermanentBuff BuffType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float BuffValue;

public:
	UPlayerPermanentBuffAbility();

	virtual void Execute() override;
};

// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NLAbility.generated.h"

class USoundCue;
class UAnimMontage;
class UParticleSystem;
class ANLPlayerController;

/**
 * 
 */
UCLASS(HideDropdown, Blueprintable)
class NEWLIFE_API UNLAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AbilityDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* AbilityIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* ExecuteSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* MontageToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* ExecuteParticle;

public:
	UNLAbility();

	virtual bool TryExecute(ANLPlayerController* PlayerController);

protected:
	void GenerateEffects();

	virtual bool IsExecutable(ANLPlayerController* PlayerController);

public:
	FORCEINLINE FText GetAbilityName() const { return AbilityName; }
	FORCEINLINE FText GetAbilityDescription() const { return AbilityDescription; }
	FORCEINLINE UTexture2D* GetAbilityIcon() const { return AbilityIcon; }
	FORCEINLINE void SetAbilityIcon(UTexture2D* NewIcon) { AbilityIcon = NewIcon; }
};

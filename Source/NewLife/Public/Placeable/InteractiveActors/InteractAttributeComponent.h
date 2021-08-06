// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractAttributeComponent.generated.h"

class UAnimMontage;
class UParticleSystem;
class USoundCue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEWLIFE_API UInteractAttributeComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Interactive Object Properties",
		meta=(AllowPrivateAccess="true"))
	UAnimMontage* MontageToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Interactive Object Properties",
		meta=(AllowPrivateAccess="true"))
	UParticleSystem* OnInteractParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Interactive Object Properties",
		meta=(AllowPrivateAccess="true"))
	USoundCue* OnInteractSound;

public:
	UInteractAttributeComponent();

	void GenerateInteractionEffects(APawn* PlayerPawn) const;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE UAnimMontage* GetMontageToPlay() const { return MontageToPlay; }
};

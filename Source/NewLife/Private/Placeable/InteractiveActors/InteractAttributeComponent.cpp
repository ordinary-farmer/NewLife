// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Placeable/InteractiveActors/InteractAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInteractAttributeComponent::UInteractAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInteractAttributeComponent::GenerateInteractionEffects(APawn* PlayerPawn) const
{
	UWorld* ThisWorld = GetWorld();
	AActor* Owner = GetOwner();
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerPawn);

	if(PlayerCharacter)
	{
		PlayerCharacter->PlayAnimMontage(MontageToPlay);
	}
	
	if (ThisWorld && Owner)
	{
		if (OnInteractParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(ThisWorld, OnInteractParticle, Owner->GetActorLocation());
		}

		if (OnInteractSound)
		{
			UGameplayStatics::PlaySound2D(ThisWorld, OnInteractSound);
		}
	}
}


void UInteractAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


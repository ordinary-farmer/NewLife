// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayMessageHandlerSubsystem.generated.h"

class UDataTable;
class UUWGameplayMessageHandler;

/**
 * 
 */
UCLASS()
class NEWLIFE_API UGameplayMessageHandlerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* GameplayMessageTable;

	UPROPERTY()
	UUWGameplayMessageHandler* MessageHandler;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void DisplayMessage(FString MessageKey);

public:
	FORCEINLINE void SetMessageHandler(UUWGameplayMessageHandler* NewMessageHandler)
	{
		MessageHandler = NewMessageHandler;
	}
};

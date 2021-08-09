// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWGameplayMessageHandler.h"
#include "Components/TextBlock.h"
#include "Singleton/GameplayMessageHandlerSubsystem.h"

void UUWGameplayMessageHandler::DisplayMessage(FText Message)
{
	FTimerManager& WorldTimerManager = GetWorld()->GetTimerManager();
	
	if(WorldTimerManager.IsTimerActive(MessageTimerHandle))
	{
		WorldTimerManager.ClearTimer(MessageTimerHandle);
	}
	
	MessageTextBlock->SetText(Message);
	MessageTextBlock->SetColorAndOpacity(TextColor);
	
	WorldTimerManager.SetTimer(MessageTimerHandle, this, &UUWGameplayMessageHandler::HideMessage, 3.f);
}

void UUWGameplayMessageHandler::NativePreConstruct()
{
	MessageTextBlock->SetColorAndOpacity(TextColor);
}

void UUWGameplayMessageHandler::NativeConstruct()
{
	UGameInstance* GameInstance = GetGameInstance();
	UGameplayMessageHandlerSubsystem* MessageHandlerSubsystem = GameInstance->GetSubsystem<UGameplayMessageHandlerSubsystem>();
	MessageHandlerSubsystem->SetMessageHandler(this);

	MessageTextBlock->SetColorAndOpacity(InitialTextColor);
}

void UUWGameplayMessageHandler::HideMessage()
{
	PlayAnimation(HideMessageAnimation);
}

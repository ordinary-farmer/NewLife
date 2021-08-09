// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Singleton/GameplayMessageHandlerSubsystem.h"
#include "Engine/DataTable.h"
#include "UMG/UWGameplayMessageHandler.h"
#include "TableRowBase/GameplayMessageRow.h"

void UGameplayMessageHandlerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	GameplayMessageTable = LoadObject<UDataTable>(this, TEXT("DataTable'/Game/_NewLife/DataTable/GameplayMessageTable.GameplayMessageTable'"));
	check(GameplayMessageTable);
}

void UGameplayMessageHandlerSubsystem::Deinitialize()
{
}

void UGameplayMessageHandlerSubsystem::DisplayMessage(FString MessageKey)
{
	check(GameplayMessageTable);
	check(MessageHandler);

	MessageHandler->DisplayMessage(GameplayMessageTable->FindRow<FGameplayMessageRow>(*MessageKey, TEXT(""))->Message);
}

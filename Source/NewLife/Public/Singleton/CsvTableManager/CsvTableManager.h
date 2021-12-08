// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CsvTableManager.generated.h"

#define CSV_FILE_EXTENSION (TEXT("csv"))
#define BASE_DIRECTORY_NAME (TEXT("CsvTables"))
#define ROOT_DIRECTORY_NAME (TEXT("Root"))
#define SLASH (TEXT("/"))

/**
* @brief Csv Table Manager Singleton class.
*/
UCLASS()
class NEWLIFE_API UCsvTableManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
};

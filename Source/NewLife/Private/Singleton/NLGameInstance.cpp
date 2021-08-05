// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/NLGameInstance.h"
#include "Engine/DataTable.h"

UNLGameInstance::UNLGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CamMoveInfoDTAsset(TEXT("DataTable'/Game/_NewLife/DataTable/CamMoveDataTable.CamMoveDataTable'"));

	if(CamMoveInfoDTAsset.Succeeded())
	{
		CameraMoveInfoTable = CamMoveInfoDTAsset.Object;
	}
}

void UNLGameInstance::Init()
{
	Super::Init();
}

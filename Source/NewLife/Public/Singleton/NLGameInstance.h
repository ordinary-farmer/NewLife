// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NLGameInstance.generated.h"

class UDataTable;

UCLASS()
class NEWLIFE_API UNLGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* CameraMoveInfoTable;
	
public:
	UNLGameInstance();

	virtual void Init() override;

	FORCEINLINE UDataTable* GetCameraMoveInfoTable() const { return CameraMoveInfoTable; }
};

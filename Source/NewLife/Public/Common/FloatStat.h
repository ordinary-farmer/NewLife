// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "FloatStat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentFloatStatChangedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentFloatStatUnderMinSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMaxFloatStatChangedSignature);

USTRUCT(BlueprintType)
struct FFloatStat
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Min;

	UPROPERTY(BlueprintReadOnly)
	float MinOfMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Max;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCurrentFloatStatChangedSignature OnCurrentChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCurrentFloatStatUnderMinSignature OnCurrentUnderMin;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnMaxFloatStatChangedSignature OnMaxChanged;
	
	FFloatStat();
	FFloatStat(float DefaultCurrent, float DefaultMax, float DefaultMin = 0.f);
	virtual ~FFloatStat();

	void SetData(float NewCurrent, float NewMax);

	void IncreaseCurrent(float Value);

	void DecreaseCurrent(float Value);

	void IncreaseMax(float Value);

	void DecreaseMax(float Value);

	FORCEINLINE float GetCurrent() const { return Current; }

	FORCEINLINE float GetMin() const { return Min; }

	FORCEINLINE float GetMax() const { return Max; }
};


// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"
#include "Int32Stat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentInt32StatChangedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentInt32StatUnderMinSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMaxInt32StatChangedSignature);

USTRUCT(BlueprintType)
struct FInt32Stat
{
	GENERATED_BODY()

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Min;

	UPROPERTY(BlueprintReadOnly)
	int32 MinOfMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Max;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCurrentInt32StatChangedSignature OnCurrentChanged;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnCurrentInt32StatUnderMinSignature OnCurrentUnderMin;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatcher")
	FOnMaxInt32StatChangedSignature OnMaxChanged;
	
	FInt32Stat();
	FInt32Stat(int32 DefaultCurrent, int32 DefaultMax, int32 DefaultMin = 0);
	virtual ~FInt32Stat();

	void SetData(int32 NewCurrent, int32 NewMax);

	void IncreaseCurrent(int32 Value);

	void DecreaseCurrent(int32 Value);

	void IncreaseMax(int32 Value);

	void DecreaseMax(int32 Value);

	FORCEINLINE int32 GetCurrent() const { return Current; }

	FORCEINLINE int32 GetMin() const { return Min; }

	FORCEINLINE int32 GetMax() const { return Max; }
};

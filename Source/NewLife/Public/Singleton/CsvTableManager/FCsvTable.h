// Made By Park Joo Hyeong. This is my first Portfollio.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NEWLIFE_API FCsvTable
{
	friend class UCsvTableManager;
	
public:
	FCsvTable(FString TableID, FString Path);
	FCsvTable(const FCsvTable& Other) = delete;
	FCsvTable& operator=(const FCsvTable& Rhs) = delete;
	~FCsvTable() = default;
	
	/**
	* @brief Get Row Data.
	* @tparam S UE4 Struct Type. It has to match Row data type.
	* @param RowID RowID to find Row data.
	* @return Returns empty data if it fails.
	*/
	template <typename S>
    S TryGetRow(FString RowID) const;

	/**
	* @brief Get this TableID.
	*/
	FORCEINLINE const FString& GetTableID() const { return TableID; }

	/**
	* @brief Get this CSV file path.
	*/
	FORCEINLINE const FString& GetPath() const { return Path; }
	
	private:
	/**
	* @brief Load Csv File.
	*/
	void Load();

	/**
	* @brief Unload Table.
	*/
	void UnLoad();
	
	/**
	* @brief Remove White Spaces and Parenthesis.
	* @param InStr InStr will be modified.
	*/
	static void RemoveWhiteSpacesAndParenthesis(FString& InStr);
	
	/**
	* @brief Assign Single Value.
	* @param ContainerPtr Container pointer of property.
	* @param Property Property pointer to Value.
	* @param Cell Cell contains real data.
	* @return True if success.
	*/
	static bool AssignSingleValue(void* ContainerPtr, FProperty* Property, FString& Cell);

	/**
	* @brief Assign Array Value.
	* @param ContainerPtr Container pointer of property.
	* @param ArrayProperty Array property pointer to Value.
	* @param Cell Cell contains real data.
	* @return True if success.
	*/
	static bool AssignArrayValue(void* ContainerPtr, FArrayProperty* ArrayProperty, FString& Cell);
	
	/** Table ID. */
	FString TableID;

	/** File path of this Table. */
	FString Path;
	
	/** Key is Property Name, Value is Property's Index. */
	TMap<FString, int32> PropertyIndex;

	/** Key is Row ID, Value is Array of Data */
	TMap<FString, TArray<FString>> Rows;

	/** If Table is loaded, it will be set to true. */
	bool bIsLoaded;	
};


template <typename S>
S FCsvTable::TryGetRow(FString RowID) const
{
	S Result;
	S Fail;
	
	// Check S and RowID is valid first.	
	if(bIsLoaded == false || Rows.Find(RowID) == nullptr)
	{
		return Fail;
	}
	
	TArray<FString> Row = *Rows.Find(RowID);	

	for(TFieldIterator<FProperty> Iter(Result.StaticStruct()); Iter; ++Iter)
	{
		if(PropertyIndex.Find(Iter->GetName()) == nullptr)
		{
			return Fail;
		}
	}

	// Do Work
	for(TFieldIterator<FProperty> Iter(Result.StaticStruct()); Iter; ++Iter)
	{
		const int32 Index = *PropertyIndex.Find(Iter->GetName());
		FString& Cell = Row[Index - 1];

		RemoveWhiteSpacesAndParenthesis(Cell);
		
		if(Iter->GetCPPType() == "TArray")
		{
			FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*Iter);

			if(AssignArrayValue(&Result, ArrayProperty, Cell) == false)
			{
				return Fail;
			}
		}
		else
		{			
			if(AssignSingleValue(&Result, *Iter, Cell) == false)
			{
				return Fail;
			}
		}
	}	

	return Result;
}

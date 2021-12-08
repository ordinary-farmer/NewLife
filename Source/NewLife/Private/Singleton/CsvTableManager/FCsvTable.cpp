// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Singleton/CsvTableManager/FCsvTable.h"
#include "Logging/MessageLog.h"

FCsvTable::FCsvTable(FString TableID, FString Path)
	: TableID(TableID)
	, Path(Path)
	, bIsLoaded(false)
{
}

void FCsvTable::Load()
{
	if(bIsLoaded)
	{
		return;
	}

	FMessageLog Logger("LoadErrors");
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	TArray<FString> Lines;
	FFileHelper::LoadFileToStringArray(Lines, *Path);

	if(Lines.Num() <= 1)
	{
		Logger.Error(FText::FromString(FString::Printf(TEXT("%s: CSV File Load Fail! No data is required. Path: %s"), *TableID, *Path)));
		return;
	}

	// Set Properties
	{
		const TCHAR* Start = *Lines[0];
		const TCHAR* Delim = TEXT(",");
		const int32 DelimLength = FCString::Strlen(Delim);
	
		if (Start && *Start != TEXT('\0') && DelimLength)
		{
			int32 Index = 0;
			while( const TCHAR *At = FCString::Strstr(Start,TEXT(",")) )
			{
				if (At-Start)
				{
					FString Tmp(UE_PTRDIFF_TO_INT32(At-Start),Start);
					PropertyIndex.Emplace(Tmp, Index);
				}
				Start = At + DelimLength;
				Index++;
			}
			if (*Start)
			{
				PropertyIndex.Emplace(Start, Index);
			}
		}

		if(PropertyIndex.Num() <= 1)
		{
			Logger.Error(FText::FromString(FString::Printf(TEXT("%s: CSV File Load Fail! No data is required. Path: %s"), *TableID, *Path)));
			PropertyIndex.Empty();
			return;
		}
	}

	// Set Rows
	{
		for(int32 i = 1; i < Lines.Num(); ++i)
		{			
			const TCHAR* Start = *Lines[i];
			const TCHAR* Delim = TEXT(",");
			const int32 DelimLength = FCString::Strlen(Delim);

			const TCHAR *At = FCString::Strstr(Start,TEXT(","));
			FString Key(UE_PTRDIFF_TO_INT32(At-Start),Start);
			Start = At + DelimLength;

			TArray<FString> Values;

			if (Start && *Start != TEXT('\0') && DelimLength)
			{
				while( (At = FCString::Strstr(Start,TEXT(","))) != nullptr )
				{
					if (At-Start)
					{
						Values.Emplace(UE_PTRDIFF_TO_INT32(At-Start),Start);
					}
					Start = At + DelimLength;
				}
				if (*Start)
				{
					Values.Emplace(Start);
				}
			}

			Rows.Emplace(Key, Values);			
		}
	}

	bIsLoaded = true;	
}

void FCsvTable::UnLoad()
{
	PropertyIndex.Empty();
	Rows.Empty();
	bIsLoaded = false;
}

void FCsvTable::RemoveWhiteSpacesAndParenthesis(FString& InStr)
{
	int32 Pos = 0;
	
	while(Pos < InStr.Len())
	{
		if(FChar::IsWhitespace(InStr[Pos]) || InStr[Pos] == '(' || InStr[Pos] == ')')
		{
			InStr.RemoveAt(Pos, 1, false);
		}
		else
		{
			Pos++;
		}
	}
}

bool FCsvTable::AssignSingleValue(void* ContainerPtr, FProperty* Property, FString& Cell)
{
	bool bResult = true;
	
	if(Property->GetCPPType() == "bool")
	{
		bool* ValuePtr = Property->ContainerPtrToValuePtr<bool>(ContainerPtr);
		*ValuePtr = Cell.ToBool();
	}
	else if(Property->GetCPPType() == "uint8")
	{
		uint8* ValuePtr = Property->ContainerPtrToValuePtr<uint8>(ContainerPtr);
		const int32 Tmp = FCString::Atoi(*Cell);
		*ValuePtr = static_cast<uint8>(Tmp);
	}
	else if(Property->GetCPPType() == "int32")
	{
		int32* ValuePtr = Property->ContainerPtrToValuePtr<int32>(ContainerPtr);
		*ValuePtr = FCString::Atoi(*Cell);
	}
	else if(Property->GetCPPType() == "int64")
	{
		int64* ValuePtr = Property->ContainerPtrToValuePtr<int64>(ContainerPtr);
		*ValuePtr = FCString::Atoi64(*Cell);
	}
	else if(Property->GetCPPType() == "float")
	{
		float* ValuePtr = Property->ContainerPtrToValuePtr<float>(ContainerPtr);
		*ValuePtr = FCString::Atof(*Cell);
	}
	else if(Property->GetCPPType() == "FName")
	{
		FName* ValuePtr = Property->ContainerPtrToValuePtr<FName>(ContainerPtr);		
		*ValuePtr = FName(*Cell.TrimQuotes());
	}
	else if(Property->GetCPPType() == "FString")
	{
		FString* ValuePtr = Property->ContainerPtrToValuePtr<FString>(ContainerPtr);
		*ValuePtr = Cell.TrimQuotes();
	}
	else if(Property->GetCPPType() == "FVector")
	{
		FVector* ValuePtr = Property->ContainerPtrToValuePtr<FVector>(ContainerPtr);
		FVector Tmp;
		Tmp.InitFromString(Cell);
		*ValuePtr = Tmp;
	}
	else if(Property->GetCPPType() == "FRotator")
	{
		FRotator* ValuePtr = Property->ContainerPtrToValuePtr<FRotator>(ContainerPtr);
		FRotator Tmp;
		Tmp.InitFromString(Cell);
		*ValuePtr = Tmp;
	}
	else
	{
		bResult = false;
	}

	return bResult;
}

bool FCsvTable::AssignArrayValue(void* ContainerPtr, FArrayProperty* ArrayProperty, FString& Cell)
{
	TArray<FString> Elements;

	Cell.ParseIntoArray(Elements, TEXT(","), false);
	
	FScriptArrayHelper ArrayHelper(ArrayProperty, ArrayProperty->ContainerPtrToValuePtr<void>(ContainerPtr));
	ArrayHelper.AddValues(Elements.Num());

	uint8* ValuePtr = ArrayHelper.GetRawPtr();

	const int32 ElementSize = ArrayProperty->Inner->ElementSize;

	for(int32 i = 0; i < Elements.Num(); ++i)
	{
		if(ArrayProperty->Inner->GetCPPType() == "bool")
		{
			*(reinterpret_cast<bool*>(ValuePtr)) = Elements[i].ToBool();
		}
		else if(ArrayProperty->Inner->GetCPPType() == "uint8")
		{
			const int32 Tmp = FCString::Atoi(*Elements[i]);
			*(reinterpret_cast<uint8*>(ValuePtr)) = static_cast<uint8>(Tmp);
		}
		else if(ArrayProperty->Inner->GetCPPType() == "int32")
		{
			*(reinterpret_cast<int32*>(ValuePtr)) = FCString::Atoi(*Elements[i]);
		}
		else if(ArrayProperty->Inner->GetCPPType() == "int64")
		{
			*(reinterpret_cast<int64*>(ValuePtr)) = FCString::Atoi64(*Elements[i]);
		}
		else if(ArrayProperty->Inner->GetCPPType() == "float")
		{
			*(reinterpret_cast<float*>(ValuePtr)) = FCString::Atof(*Elements[i]);
		}
		else if(ArrayProperty->Inner->GetCPPType() == "FName")
		{
			*(reinterpret_cast<FName*>(ValuePtr)) = FName(*Elements[i].TrimQuotes());
		}
		else if(ArrayProperty->Inner->GetCPPType() == "FString")
		{
			*(reinterpret_cast<FString*>(ValuePtr)) = Elements[i].TrimQuotes();
		}
		else if(ArrayProperty->Inner->GetCPPType() == "FVector")
		{
			FVector Tmp;
			Tmp.InitFromString(Elements[i]);
			*(reinterpret_cast<FVector*>(ValuePtr)) = Tmp;
		}
		else if(ArrayProperty->Inner->GetCPPType() == "FRotator")
		{
			FRotator Tmp;
			Tmp.InitFromString(Elements[i]);
			*(reinterpret_cast<FRotator*>(ValuePtr)) = Tmp;
		}
		else
		{
			return false;
		}

		ValuePtr += ElementSize;
	}	

	return true;
}

